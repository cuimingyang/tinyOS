#ifndef __TINY_OS_SEMAPHORE_H__
#define __TINY_OS_SEMAPHORE_H__


#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief 创建并初始化信号量
 * 
 * @param：pSemHandle，信号量句柄
 * @param：uiSemCnt，信号量初始值 
 * @param：uiSemMax，最大计数值，当信号到达这个值后，就不再增长 
 * @return 0=成功，非0=失败
 */
OPERATE_RET tiny_os_semaphore_create_init(OUT SEM_HANDLE *pSemHandle, IN CONST UINT_T uiSemCnt, IN CONST UINT_T uiSemMax)
{

}

/**
 * @brief：等待信号量
 *
 * @param：semHandle，信号量句柄
 * @param：uiTimeout，超时时间(TINY_OS_SEM_FOREVER:表示永久阻塞)
 * @return 0=成功，非0=失败
*/
OPERATE_RET tiny_os_semaphore_wait(IN CONST SEM_HANDLE semHandle, IN UINT_T uiTimeout)
{

}

/**
 * @brief：释放信号量，唤醒挂在该信号量上的线程
 * 
 * @param：semHandle，信号量句柄
 * @return：0=成功，非0=失败
 */
OPERATE_RET tiny_os_semaphore_post(IN CONST SEM_HANDLE semHandle)
{

}

/**
 * @brief：删除信号量释放系统资源，适用于动态创建的信号量
 * 
 * @param：semHandle，信号量句柄 
 * @return 0=成功，非0=失败
 */
OPERATE_RET tiny_os_semaphore_delete(IN CONST SEM_HANDLE semHandle)
{

}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

