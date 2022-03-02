#ifndef __TINY_OS_THREAD_H__
#define __TINY_OS_THREAD_H__


#ifdef __cplusplus
extern "C" {
#endif


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
OPERATE_RET tiny_os_thread_create(OUT THREAD_HANDLE* pThreadHandle, IN CONST CHAR_T* pcName, IN UINT_T uiStackSize, IN UINT_T uiPriority, IN THREAD_pFunc_T pFunc, IN VOID* CONST pvArg)
{

}

/**
 * @brief：删除线程
 * 
 * @param：threadHandle，线程句柄
 * @return: 0=success， other=fail
 */
OPERATE_RET tiny_os_thread_delete(IN THREAD_HANDLE threadHandle)
{

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


}

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __TINY_OS_THREAD_H__

