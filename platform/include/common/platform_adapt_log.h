#ifndef __PLATFORM_ADAPT_LOG_H__
#define __PLATFORM_ADAPT_LOG_H__

#include "platform_adapt_type.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef INT_T LOG_LEVEL;
#define LOG_LEVEL_ERR       0  // 错误信息，程序正常运行不应发生的信息 
#define LOG_LEVEL_WARN      1  // 警告信息
#define LOG_LEVEL_NOTICE    2  // 需要注意的信息
#define LOG_LEVEL_INFO      3  // 通知信息
#define LOG_LEVEL_DEBUG     4  // 程序运行调试信息，RELEASE版本中删除
#define LOG_LEVEL_TRACE     5  // 程序运行路径信息，RELEASE版本中删除



#define PR_ERR(fmt, ...)    //SAK_PRINT_ERR_LOG(fmt, ##__VA_ARGS__)
#define PR_WARN(fmt, ...)   //SAK_PRINT_WARN_LOG(fmt, ##__VA_ARGS__)
#define PR_NOTICE(fmt, ...) //SAK_PRINT_NOTICE_LOG(fmt, ##__VA_ARGS__)
#define PR_INFO(fmt, ...)   //SAK_PRINT_INFO_LOG(fmt, ##__VA_ARGS__)
#define PR_DEBUG(fmt, ...)  //SAK_PRINT_DEBUG_LOG(fmt, ##__VA_ARGS__)


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


