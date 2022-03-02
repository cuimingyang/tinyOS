#ifndef __TINY_OS_QUEUE_H__
#define __TINY_OS_QUEUE_H__


#ifdef __cplusplus
extern "C" {
#endif

#define TINY_OS_QUEUE_FOREVER 0xffffffff

/**
 * @brief：创建消息队列
 * @param: pQueueHandle, 消息队列句柄
 * @param：uiMsgMaxSize，消息队列最大个数
 * @return：OPRT_OK: success， other: fail
 */
OPERATE_RET tiny_os_queue_create_init(OUT QUEUE_HANDLE *pQueueHandle, IN UINT_T uiMsgMaxSize)
{

}

/**
 * @brief：删除消息队列
 * @param: queueHandle, 消息队列句柄
 * @return：OPRT_OK: success， other: fail
 */
OPERATE_RET tiny_os_queue_create_init(IN QUEUE_HANDLE queueHandle)
{

}

/**
 * @brief: 发送消息
 * @param: queueHandle, 消息队列句柄
 * @param：pvData, 消息内容
 * @param：uiSize, 消息大小
 * @param: uiTimeoutMs, 发送超时时间，TINY_OS_QUEUE_FOREVER means forever wait
 * @return  int OPRT_OS_ADAPTER_OK:success    other:fail
 */
OPERATE_RET tiny_os_queue_send(IN QUEUE_HANDLE queueHandle, IN CONST VOID *pvMsgData, IN UINT_T uiSize, IN UINT_T uiTimeoutMs)
{

}

/**
 * @brief: 接收消息
 * @param: queueHandle, 消息队列句柄
 * @param：pvData, 消息内容
 * @param：uiSize, 消息大小
 * @param: uiTimeoutMs, 超时时间，TINY_OS_QUEUE_FOREVER means forever wait
 * @return  int OPRT_OS_ADAPTER_OK:success    other:fail
 */
OPERATE_RET tiny_os_queue_recv(IN QUEUE_HANDLE queueHandle, OUT CONST VOID *pvMsgData, IN UINT_T uiSize, IN UINT_T uiTimeoutMs)
{
    
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
