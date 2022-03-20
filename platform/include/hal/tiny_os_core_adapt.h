#ifndef __TINY_OS_CORE_ADAPT_H__
#define __TINY_OS_CORE_ADAPT_H__

#include "platform_adapt_type.h"

#ifdef __cplusplus
extern "C" {
#endif

///> 进入临界区
extern UINT_T hal_thread_enter_critical(VOID);

///> 退出临界区
extern VOID hal_thread_exit_critical(UINT_T uiCpuStatus);

///> 任务切换
extern VOID hal_thread_switch(VOID);

///> 启动tinyOS时，切换至第一个任务运行
extern VOID hal_thread_run_first(VOID);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* __TINY_OS_CORE_ADAPT_H__ */


