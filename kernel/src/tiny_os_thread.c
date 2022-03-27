/*
 * @brief: 实现线程相关接口
 * @author: cuimy
 * @email: 2604325078@qq.com
 * @date: 2022-02-27
 * @Copyright: 
 */

#include "tiny_os_type.h"
#include "tiny_os_thread.h"
#include "tiny_os_core_adapt.h"
#include "double_list.h"
#include "bit_map.h"

#define TINYOS_TASK_STATE_RDY                   0
#define TINYOS_TASK_STATE_DESTROYED             (1 << 0)
#define TINYOS_TASK_STATE_DELAYED               (1 << 1)
#define TINYOS_TASK_STATE_SUSPEND               (1 << 2)
#define TINYOS_TASK_WAIT_MASK                   (0xFF << 16)


///> 根据已知节点，访问父结构
#define GET_PARENT_BY_NODE(node, parent, name) (parent *)((UINT_T)node - (UINT_T)&((parent *)0)->name)



typedef struct _NODE_S {
    struct _NODE_S *tPreNode;
    struct _NODE_S *tNextNode;
}LIST_NODE_S;

///> tinyOS链表类型
typedef struct _tList {
    LIST_NODE_S tHeadNode;
    UINT_T uiNodeCnt;
}LINK_LIST_S;

///> 任务结构：包含了一个任务的所有信息
///> 1.任务所用堆栈的当前堆栈指针。每个任务都有他自己的堆栈，用于在运行过程中存储临时变量等一些环境参数
///> 2.在tinyOS运行该任务前，会从stack指向的位置处，会读取堆栈中的环境参数恢复到CPU寄存器中，然后开始运行
///> 3.在切换至其它任务时，会将当前CPU寄存器值保存到堆栈中，等待下一次运行该任务时再恢复。
typedef struct{
    UINT_T *puiStackResume;                   ///< 保存了最后保存环境参数的地址位置，用于后续恢复
    UINT_T *puiStackBase;                     ///< 堆栈的起即地址
    UINT_T uiStackSize;                       ///< 堆栈的总容量
    LIST_NODE_S tLinkNode;                    ///< 连接结点
    UINT_T uiDelayTicks;                      ///< 任务延时计数器
    LIST_NODE_S tDelayNode;                   ///< 延时结点, 将THREAD_HANDLE_S放置到延时队列中
    UINT_T uiPrio;                            ///< 任务的优先级
    UINT_T uiCurState;                        ///< 任务当前状态
    UINT_T uiRemainSlice;                     ///< 当前剩余的时间片
    UINT_T uiSuspendCnt;                      ///< 被挂起的次数
    VOID (*pFnThreadDestroy)(VOID *pvParam);  ///< 任务被删除时调用的清理函数
    VOID *pvDestroyParam;                     ///< 传递给清理函数的参数
    UCHAR_T ucReqDelFlag;                     ///< 请求删除标志，非0表示请求删除
}THREAD_HANDLE_S;


///> 任务相关信息结构
typedef struct{
    UINT_T uiDelayTicks;                   ///< 任务延时计数器
    UINT_T uiPrio;                         ///< 任务的优先级
    UINT_T uiCurState;                     ///< 任务当前状态
    UINT_T uiRemainSlice;                  ///< 当前剩余的时间片
    UINT_T uiSuspendCnt;                   ///< 被挂起的次数
    UINT_T uiStackSize;                    ///< 堆栈的总容量
    UINT_T uiStackFreeSize;                ///< 堆栈空余量
}THREAD_INFO_S;


typedef struct{
    THREAD_HANDLE_S *ptCurThread;          ///< 当前任务：记录当前是哪个任务正在运行
    THREAD_HANDLE_S *ptNextThread;         ///< 下一个将即运行的任务
    THREAD_HANDLE_S *ptIdleThread;         ///< 空闲任务
    BIT_MAP_S tPrioBitmap;                 ///< 任务优先级的标记位置结构
    UCHAR_T ucSchedLockCnt;                ///< 调度锁计数器
    UINT_T uiTickCnt;                      ///< 时钟节拍计数
    LINK_LIST_S tDelayList;                ///< 延时队列
    UINT_T uiIdleCnt;                      ///< 空闲任务计数
    UINT_T uiIdleMaxCnt;                   ///< 空闲任务最大计数
    LINK_LIST_S tThreadTable[TINYOS_PRO_COUNT];   ///< 所有任务的指针数组
}THREAD_SCHED_S;


STATIC THREAD_SCHED_S tThreadSched;


///> 系统节拍通知
WEAK VOID tiny_os_systick_notify(VOID)
{

}

///> 进入临界区
STATIC UINT_T __thread_enter_critical(VOID) 
{
    hal_thread_enter_critical();
}

///> 退出临界区
STATIC VOID __thread_exit_critical(UINT_T uiCpuStatus)
{
    hal_thread_exit_critical(uiCpuStatus);
}

///> 任务切换
STATIC VOID __thread_switch(VOID)
{
    hal_thread_switch();
}

///> 获取当前最高优先级且可运行的任务
STATIC THREAD_HANDLE_S *__thread_get_highest_ready(VOID)
{
    UINT_T uiHighestPrio;
    LIST_NODE_S *ptNode = NULL;
    
    uiHighestPrio = bit_map_first_valid_pos_get(&tThreadSched.tPrioBitmap);
    ptNode = double_list_get_head_node(&tThreadSched.tThreadTable[uiHighestPrio]);
    
    return (THREAD_HANDLE_S *)GET_PARENT_BY_NODE(ptNode, THREAD_HANDLE_S, tLinkNode);
}

///> 初始化调度器
STATIC VOID __thread_sched_init(VOID) 
{
    UINT_T i = 0;

    tThreadSched.ucSchedLockCnt = 0;
    bit_map_init(&tThreadSched.tPrioBitmap);

    for(i = 0; i < TINYOS_PRO_COUNT; i++){
        double_list_create(&tThreadSched.tThreadTable[i]);
    }
}

///> 禁止任务调度
STATIC VOID __thread_sched_disable(VOID)
{
    UINT_T uiStatus = __thread_enter_critical();

    if(tThreadSched.ucSchedLockCnt < 255){
        tThreadSched.ucSchedLockCnt++;
    }

    __thread_exit_critical(uiStatus);
}

///> 允许任务调度
STATIC VOID __thread_sched_enable(VOID)
{
    UINT_T uiStatus = __thread_enter_critical();

    if(tThreadSched.ucSchedLockCnt > 0) {
        if (0 == --tThreadSched.ucSchedLockCnt) {
            __thread_sched();
        }
    }

    __thread_exit_critical(uiStatus);
}

///> 将任务设置为就绪状态
STATIC VOID __thread_sched_ready(THREAD_HANDLE_S *ptThread)
{
    double_list_insert_tail_node(&tThreadSched.tThreadTable[ptThread->uiPrio], ptThread->tLinkNode);
    bit_map_set(tThreadSched.tPrioBitmap, ptThread->uiPrio);
}

/**
 * @brief 将任务从就绪列表中移除
 * @param task 等待取消就绪的任务
 */
VOID __thread_sched_unready(THREAD_HANDLE_S *ptThread)
{
    double_list_remove_node(&tThreadSched.tThreadTable[ptThread->uiPrio], &(ptThread->tLinkNode));

    ///> 队列中可能存在多个任务。只有当没有任务时，才清除位图标记
    if(0 == double_list_get_node_num(&tThreadSched.tThreadTable[ptThread->uiPrio])){
        bit_map_clear(tThreadSched.tPrioBitmap, ptThread->uiPrio);
    }
}

///> 将延时的任务从延时队列中移除
VOID __thread_delay_list_remove(THREAD_HANDLE_S *ptThread)
{    
    double_list_remove_node(tThreadSched.tDelayList, ptThread->tDelayNode);
}

///> 将任务从就绪列表中移除
STATIC VOID __thread_sched_list_remove(THREAD_HANDLE_S *ptThread) 
{
    double_list_remove_node(&tThreadSched.tThreadTable[ptThread->uiPrio], &(ptThread->tLinkNode));
    
    if(0 == double_list_get_node_num(&tThreadSched.tThreadTable[ptThread->uiPrio])){
        bit_map_clear(tThreadSched.tPrioBitmap, ptThread->uiPrio);
    }
}


///> 线程调度
STATIC VOID __thread_sched(VOID)
{
    UINT_T uiStatus = __thread_enter_critical();

    if(tThreadSched.ucSchedLockCnt > 0){
        __thread_exit_critical(uiStatus); ///< 调度器已上锁，直接退出
        return;
    }

    THREAD_HANDLE_S ptThread;

    ptThread = __thread_get_highest_ready();
    if(ptThread != tThreadSched.ptCurThread){
        tThreadSched.ptNextThread = ptThread;

        __thread_switch();
    }
    
    ///> 退出临界区
    __thread_exit_critical(uiStatus);
}

///> 将延时的任务从延时队列中唤醒
STATIC VOID __thread_delayed_wake_up(THREAD_HANDLE_S *ptThread)
{
    ptThread->uiDelayTicks = 0;
    
    double_list_remove_node(&tThreadSched.tDelayList, &(ptThread->tDelayNode));
    ptThread->uiCurState &= ~TINYOS_TASK_STATE_DELAYED;
}


///> 将任务设置为就绪状态
STATIC VOID __thread_set_ready_state(THREAD_HANDLE_S *ptThread)
{
    double_list_insert_after_node(&tThreadSched.tThreadTable[ptThread->uiPrio], &(ptThread->tLinkNode));
    bit_map_set(&tThreadSched.tPrioBitmap, ptThread->uiPrio);
}

/**
 * 保存前一任务栈地址，获取下一任务栈地址
 * @param stackAddr 前一任务栈地址
 * @return 下一要运行的任务栈地址
 */
UINT_T thread_save_and_load_stack(UINT_T uiStackAddr) 
{
    if(tThreadSched.ptCurThread != (THREAD_HANDLE_S*)0){
        tThreadSched.ptCurThread = (UINT_T*)uiStackAddr;
    }

    tThreadSched.ptCurThread = tThreadSched.ptNextThread;
    
    return (UINT_T)tThreadSched.ptCurThread->puiStackResume;
}


///> system tick
VOID tiny_os_system_tick_handle(VOID)
{
    LIST_NODE_S *ptNode;
    UINT_T uiCnt;

    ///> 进入临界区，保证在整个任务调度与切换期间，不会因为发生中断导致ptCurThread和ptNextThread可能更改；
    UINT_T uiStatus = __thread_enter_critical();

    ///> 遍历延时队列中的任务节点
    ptNode = double_list_get_head_node(&tThreadSched.tDelayList);
    for(uiCnt = double_list_get_node_num(&tThreadSched.tDelayList); uiCnt > 0; uiCnt--) {
        THREAD_HANDLE_S *ptThread = GET_PARENT_BY_NODE(ptNode, THREAD_HANDLE_S, tDelayNode);
        if(0 == --ptThread->uiDelayTicks){
            ///> 预先获取下一结点，否则下面的移除会造成问题
            ptNode = double_list_get_next_node(&tThreadSched.tDelayList, ptNode);

            ///> 将任务从延时队列中移除
            __thread_delayed_wake_up(ptThread);

            ///> 将任务恢复到就绪状态
            __thread_set_ready_state(ptThread);
        }
    }

    ///> 检查当前任务的时间片是否已经到了
    if(0 == --tThreadSched.ptCurThread->uiRemainSlice){
        // 如果当前任务中还有其它任务的话，那么切换到下一个任务
        // 方法是将当前任务从队列的头部移除，插入到尾部
        // 这样后面执行__thread_sched()时就会从头部取出新的任务取出新的任务作为当前任务运行
        if(double_list_get_node_num(&tThreadSched.tThreadTable[tThreadSched->ptCurThread->uiPrio]) > 1){
            double_list_remove_head_node(&tThreadSched.tThreadTable[tThreadSched->ptCurThread->uiPrio]);
            double_list_insert_tail_node(&tThreadSched.tThreadTable[tThreadSched->ptCurThread->uiPrio], &tThreadSched->ptCurThread->tLinkNode);
        }
        
        ///> 重载计数器
        tThreadSched.ptCurThread->uiRemainSlice = TINYOS_SLICE_MAX;
    }

    tThreadSched.uiTickCnt++;

    ///> 退出临界区
    __thread_exit_critical(uiStatus);

#if TINYOS_ENABLE_TIMER == 1
    // 通知定时器模块节拍事件
    tiny_os_systick_notify();
#endif

    ///> 这个过程中可能有任务延时完毕(uiDelayTicks = 0)，进行一次调度。
    __thread_sched();
}


/**
 * @brief: 创建线程
 * 
 * @param：pThreadHandle，线程句柄
 * @param：pcName，线程名称
 * @param：uiStackSize，线程空间大小
 * @param：uiPriority，线程优先级
 * @param：pFunc，线程入口函数
 * @param：pvArg，线程入口参数
 * @return: 0=success， other=fail
 */
OPERATE_RET tiny_os_thread_create(OUT THREAD_HANDLE* ptThreadHandle, IN CONST CHAR_T* pcName, IN UINT_T uiStackSize, IN UINT_T uiPrio, IN THREAD_pFunc_T pFunc, IN VOID* CONST pvArg)
{
    UINT_T uiStackTop;
    THREAD_HANDLE_S *ptThread = (THREAD_HANDLE_S*)&ptThreadHandle;
    ptThread->puiStackBase = tiny_os_malloc(uiStackSize);
    if(NULL == ptThread->puiStackBase){
        return OPRT_MALLOC_FAILED;
    }

    ptThread->uiStackSize = uiStackSize;
    memset(ptThread->puiStackBase, 0, uiStackSize);

    //to do 寄存器初始化

    ptThread->uiRemainSlice = TINYOS_SLICE_MAX;
    ptThread->puiStackResume = uiStackTop;
    ptThread->uiPrio = uiPrio;
    
    __thread_sched_ready(ptThreadHandle);
}


/**
 * @brief：删除线程
 * 
 * @param：threadHandle，线程句柄
 * @return: 0=success， other=fail
 */
OPERATE_RET tiny_os_thread_delete(IN THREAD_HANDLE threadHandle)
{
    UINT_T uiStatus = __thread_enter_critical();

    THREAD_HANDLE_S *ptThread = (THREAD_HANDLE_S*)&threadHandle;
    if(ptThread->uiCurState & TINYOS_TASK_STATE_DELAYED){
        __thread_delay_list_remove(ptThread);
    }else if(!(ptThread->uiCurState & TINYOS_TASK_STATE_SUSPEND)){
        __thread_sched_list_remove(ptThread);
    }

    if(tThreadSched.ptCurThread == ptThread){
        __thread_sched();
    }
    
    ///> 退出临界区
    __thread_exit_critical(uiStatus);
}

/**
* @brief: 设置线程优先级
*
* @param：threadHandle，线程句柄
* @param：uiThreadPrio，线程优先级
* @return: 0=success， other=fail
*/
OPERATE_RET tiny_os_thread_priority_set(IN THREAD_HANDLE threadHandle, IN UINT_T uiThreadPrio)
{
    UINT_T uiStatus = __thread_enter_critical();

    THREAD_HANDLE_S *ptThread = (THREAD_HANDLE_S*)&threadHandle;
    ptThread->uiPrio = uiThreadPrio;

    // to do , 判断是否需要调度一次；
    
    ///> 退出临界区
    __thread_exit_critical(uiStatus);
}
