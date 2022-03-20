/*
 * @brief: 实现线程调度的基本接口
 * @author: cuimy
 * @email: 2604325078@qq.com
 * @date: 2022-02-27
 * @Copyright: 
 */
#include "stm32f10x.h"
#include "tiny_os_type.h"

///> 在任务切换中，主要依赖了PendSV进行切换。PendSV其中的一个很重要的作用便是用于支持RTOS的任务切换。
///> 实现方法为：
///> 1、首先将PendSV的中断优先配置为最低。这样只有在其它所有中断完成后，才会触发该中断；
///>    实现方法为：向NVIC_SYSPRI2写NVIC_PENDSV_PRI
///> 2、在需要中断切换时，设置挂起位为1，手动触发。这样，当没有其它中断发生时，将会引发PendSV中断。
///>    实现方法为：向NVIC_INT_CTRL写NVIC_PENDSVSET
///> 3、在PendSV中，执行任务切换操作。
#define NVIC_INT_CTRL       0xE000ED04      ///> 中断控制及状态寄存器
#define NVIC_PENDSVSET      0x10000000      ///> 触发软件中断的值
#define NVIC_SYSPRI2        0xE000ED22      ///> 系统优先级寄存器
#define NVIC_PENDSV_PRI     0x000000FF      ///> 配置优先级

#define MEM32(addr)         *(volatile unsigned long *)(addr)
#define MEM8(addr)          *(volatile unsigned char *)(addr)


extern UINT_T thread_save_and_load_stack(UINT_T uiStackAddr);


///> 进入临界区
UINT_T hal_thread_enter_critical(VOID) 
{
    UINT_T primask = __get_PRIMASK();
    __disable_irq();        ///< CPSID I
    return primask;
}

///> 退出临界区
VOID hal_thread_exit_critical(UINT_T uiCpuStatus)
{
    __set_PRIMASK(uiCpuStatus);
}

///> 任务切换
VOID hal_thread_switch(VOID)
{
    ///> 和tTaskRunFirst, 这个函数会在某个任务中调用，然后触发PendSV切换至其它任务
    ///> 之后的某个时候，将会再次切换到该任务运行，此时，开始运行该行代码, 返回到
    ///> tTaskSwitch调用处继续往下运行
    MEM32(NVIC_INT_CTRL) = NVIC_PENDSVSET;  ///< 向NVIC_INT_CTRL写NVIC_PENDSVSET，用于PendSV
}

/**
 * 保存前一任务栈地址，获取下一任务栈地址
 * @param uiStackAddr 前一任务栈地址
 * @return 下一要运行的任务栈地址
 */
STATIC UINT_T __thread_save_and_load_stack(UINT_T uiStackAddr) 
{
    thread_save_and_load_stack(uiStackAddr);
}


///> PendSV异常处理函数，用于任务切换
__asm VOID PendSV_Handler (VOID) 
{ 
    IMPORT __thread_save_and_load_stack    ///< 汇编代码中导入外部符号，类似C中的extern声明
                                           ///< 进入异常前，硬件会自动将R0~R3等内核寄存器保存到PSP堆栈中
    MRS     R0, PSP                        ///< 获取PSP，其当前指向正在运行任务的栈中
    STMDB   R0!, {R4-R11}                  ///< 将未自动保存到任务栈中的R4-R11寄存器保存到任务栈

    BL      __thread_save_and_load_stack   ///< 调用saveAndLoadStackAddr,在这里负责切换堆栈

    LDMIA   R0!, {R4-R11}                  ///< 从将要运行的任务栈中，加载R4-R11的值到内核寄存器
    MSR     PSP, R0                        ///< 之后，调用PSP的栈指针为将要运行的任务本
    
    MOV     LR, #0xFFFFFFFD                ///< 指明退出异常时，使用PSP堆栈。0xFFFFFFFD含义特殊
    BX      LR                             ///< 如需了解含义，请查资料。之后退出异常，硬件自动弹出R0~R3等寄存器
}

///> 在启动tinyOS时，调用该函数，将切换至第一个任务运行
VOID hal_thread_run_first(VOID) 
{
    __set_PSP(__get_MSP());

    MEM8(NVIC_SYSPRI2) = NVIC_PENDSV_PRI;     ///< 向NVIC_SYSPRI2写NVIC_PENDSV_PRI，设置其为最低优先级

    MEM32(NVIC_INT_CTRL) = NVIC_PENDSVSET;    ///< 向NVIC_INT_CTRL写NVIC_PENDSVSET，用于PendSV

    ///< 这个函数是没有返回是因为，一旦触发PendSV后，将会在PendSV后立即进行任务切换，切换至第1个任务运行
    ///< 此后，tinyOS将负责管理所有任务的运行，永远不会返回到该函数运行
}

