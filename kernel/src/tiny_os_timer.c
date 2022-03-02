#ifndef __TINY_OS_TIMER_H__
#define __TINY_OS_TIMER_H__


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief：系统定时器初始化
 * 
 * @param：none
 * @return: 0=success， other=fail
 */
OPERATE_RET tiny_os_timer_init(VOID)
{

}

/**
 * @brief：添加一个系统定时器
 * 
 * @param：timerID, 定时器ID
 * @param：pTimerFunc, 定时器处理函数
 * @param：pTimerArg->定时器函数处理参数
 * @return: 0=success， other=fail
 */
OPERATE_RET tiny_os_add_timer(IN CONST P_TIMER_FUNC pTimerFunc, IN CONST PVOID_T pTimerArg, OUT TIMER_ID *pTimerID)
{

}

/**
 * @brief：删除一个系统定时器
 * 
 * @param：timerID, 定时器ID
 * @return: 0=success， other=fail
 */
OPERATE_RET tiny_os_delete_timer(IN CONST TIMER_ID timerID)
{

}

/**
 * @brief：停止一个系统定时器
 * 
 * @param：timerID, 定时器ID
 * @return: 0=success， other=fail
 */
OPERATE_RET tiny_os_stop_timer(IN CONST TIMER_ID timerID)
{

}

/**
 * @brief：该系统定时器是否运行
 * 
 * @param：timerID, 定时器ID
 * @return: 0=停止，1=运行
 */
BOOL_T tiny_os_is_timer_run(IN CONST TIMER_ID timerID)
{

}

/**
 * @brief：启动一个定时器
 * 
 * @param：timerID, 定时器ID
 * @param：timeCycle，定时周期
 * @param：cycleType，循环类型，单次/轮询
 * @return: 0=success， other=fail
 */
OPERATE_RET tiny_os_start_timer(IN CONST TIMER_ID timerID, IN CONST TIME_MS timeCycle, IN CONST TIMER_TYPE cycleType)
{

}

/**
 * @brief：系统定时器资源释放
 * 
 * @param：none
 * @return: 0=success， other=fail
 */
OPERATE_RET tiny_os_release_timer(VOID)
{

}

/**
 * @brief：获取定时器节点数量
 * 
 * @param：none
 * @return: 定时器数量，>=0;
 */
UINT_T tiny_os_get_timer_num(VOID)
{
    
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif








