#ifndef __TINY_OS_THREAD_H__
#define __TINY_OS_THREAD_H__


#ifdef __cplusplus
extern "C" {
#endif

#define TINYOS_PRO_COUNT                32                      // TinyOS任务的优先级序号
#define TINYOS_SLICE_MAX                10                      // 每个任务最大运行的时间片计数

#define TINYOS_IDLETASK_STACK_SIZE      1024                    // 空闲任务的堆栈单元数
#define TINYOS_TIMERTASK_STACK_SIZE     1024                    // 定时器任务的堆栈单元数
#define TINYOS_TIMERTASK_PRIO           1                       // 定时器任务的优先级

#define TINYOS_SYSTICK_MS               10                      // 时钟节拍的周期，以ms为单位

// 内核功能裁剪部分
#define TINYOS_ENABLE_SEM               1                       // 是否使能信号量
#define TINYOS_ENABLE_MUTEX             1                       // 是否使能互斥信号量
#define TINYOS_ENABLE_FLAGGROUP         1                       // 是否使能事件标志组
#define TINYOS_ENABLE_MBOX              1                       // 是否使能邮箱
#define TINYOS_ENABLE_MEMBLOCK          1                       // 是否使能存储块
#define TINYOS_ENABLE_TIMER             1                       // 是否使能定时器
#define TINYOS_ENABLE_CPUUSAGE_STAT     0                       // 是否使能CPU使用率统计
#define TINYOS_ENABLE_HOOKS             1                       // 是否使能Hooks



///> handle of thread
typedef VOID* THREAD_HANDLE;

///> thread pFunction type
typedef VOID (*THREAD_pFunc_T)(VOID*);

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
extern OPERATE_RET tiny_os_thread_create(OUT THREAD_HANDLE* pThreadHandle, IN CONST CHAR_T* pcName, IN UINT_T uiStackSize, IN UINT_T uiPriority, IN THREAD_pFunc_T pFunc, IN VOID* CONST pvArg);

/**
 * @brief：删除线程
 * 
 * @param：threadHandle，线程句柄
 * @return: 0=success， other=fail
 */
extern OPERATE_RET tiny_os_thread_delete(IN THREAD_HANDLE threadHandle);

/**
* @brief: 设置线程优先级
*
* @param：threadHandle，线程句柄
* @param：uiThreadPrio，线程优先级
* @return: 0=success， other=fail
*/
extern OPERATE_RET tiny_os_thread_priority_set(IN THREAD_HANDLE threadHandle, IN INT_T uiThreadPrio);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __TINY_OS_THREAD_H__

