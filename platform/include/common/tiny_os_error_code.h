#ifndef __PLATFORM_ADAPT_ERROR_CODE_H__
#define __PLATFORM_ADAPT_ERROR_CODE_H__

#include "platform_adapt_type.h"
#include "platform_adapt_log.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef int OPERATE_RET;
#define OPRT_OK                                            (-0x0000)  //执行成功
#define OPRT_COM_ERROR                                     (-0x0001)  //通用错误
#define OPRT_INVALID_PARM                                  (-0x0002)  //无效的入参
#define OPRT_MALLOC_FAILED                                 (-0x0003)  //内存分配失败
#define OPRT_NOT_SUPPORTED                                 (-0x0004)  //不支持
#define OPRT_NOT_FOUND                                     (-0x0006)  //没有找到对象
#define OPRT_CR_CJSON_ERR                                  (-0x0007)  //创建json对象失败
#define OPRT_CJSON_PARSE_ERR                               (-0x0008)  //json解析失败
#define OPRT_CJSON_GET_ERR                                 (-0x0009)  //获取json对象失败
#define OPRT_CR_MUTEX_ERR                                  (-0x000a)  //创建信号量失败
#define OPRT_CRC32_FAILED                                  (-0x0013)  //CRC校验失败
#define OPRT_TIMEOUT                                       (-0x0014)  //超时
#define OPRT_INDEX_OUT_OF_BOUND                            (-0x0016)  //索引越界

#define ASSERT_CHECK_NULL_RETURN(x, y)\
do{\
    if (NULL == (x)){\
        PR_ERR("%s null", #x);\
        return (y);\
    }\
}while(0)

#define ASSERT_CHECK_NULL_GOTO(x, label)\
do{\
    if (NULL == (x)){\
        PR_ERR("%s null", #x);\
        goto label;\
    }\
}while(0)

#define ASSERT_CALL_ERR_LOG(func)\
do{\
    rt = (func);\
    if (OPRT_OK != (rt))\
        PR_ERR("ret:%d", rt);\
}while(0)

#define ASSERT_CALL_ERR_GOTO(func, label)\
do{\
    rt = (func);\
    if (OPRT_OK != (rt)){\
        PR_ERR("ret:%d", rt);\
        goto label;\
    }\
}while(0)

#define ASSERT_CALL_ERR_RETURN(func)\
do{\
    rt = (func);\
    if (OPRT_OK != (rt)){\
       PR_ERR("ret:%d", rt);\
       return (rt);\
    }\
}while(0)

#define ASSERT_CALL_ERR_RETURN_VAL(func, y)\
do{\
    rt = (func);\
    if (OPRT_OK != (rt)){\
        PR_ERR("ret:%d", rt);\
        return (y);\
    }\
}while(0)

#ifdef __cplusplus
}
#endif

#endif ///< __PLATFORM_ADAPT_ERROR_CODE_H__
