#ifndef __TINY_OS_MEMORY_H__
#define __TINY_OS_MEMORY_H__



#ifdef __cplusplus
extern "C" {
#endif


extern VOID *tiny_os_malloc(CONST SIZE_T siMemSize);
extern VOID tiny_os_free(VOID* pvPtr);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __TINY_OS_MEMORY_H__

