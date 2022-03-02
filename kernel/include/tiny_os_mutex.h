#ifndef __TINY_OS_MUTEX_H__
#define __TINY_OS_MUTEX_H__


#ifdef __cplusplus
extern "C" {
#endif

typedef VOID* MUTEX_HANDLE;

/**
 * @brief: 创建并初始化mutex
 * @param: pMutexHandle, 返回mutex句柄
 * @return: 0=成功，非0=失败
 */
extern OPERATE_RET tiny_os_mutex_create_init(OUT MUTEX_HANDLE *pMutexHandle);

/**
 * @brief: lock mutex
 * @param: mutexHandle, mutex句柄
 * @return: 0=成功，非0=失败
 */
extern OPERATE_RET tiny_os_mutex_lock(IN CONST MUTEX_HANDLE mutexHandle);

/**
 * @brief: unlock mutex
 * @param: mutexHandle, mutex句柄
 * @return: int 0=成功，非0=失败
 */
extern OPERATE_RET tiny_os_mutex_unlock(IN CONST MUTEX_HANDLE mutexHandle);

/**
 * @brief: 释放 mutex
 * @param: mutexHandle, mutex句柄
 * @return: int 0=成功，非0=失败
 */
extern OPERATE_RET tiny_os_mutex_release(IN CONST MUTEX_HANDLE mutexHandle);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
