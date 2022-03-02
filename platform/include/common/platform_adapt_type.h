#ifndef __PLATFORM_ADAPT_TYPE_H__
#define __PLATFORM_ADAPT_TYPE_H__

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#ifndef WEAK
#define WEAK __attribute__((weak))
#endif

#ifndef VOID
typedef void VOID;
#endif
typedef void *PVOID_T;

#ifndef bool_t
typedef int bool_t;
#endif
typedef bool_t BOOL_T;
typedef BOOL_T *PBOOL_T;

typedef char CHAR_T;
typedef signed char SCHAR_T;
typedef unsigned char UCHAR_T;
typedef char *PCHAR_T;

typedef short SHORT_T;
typedef unsigned short USHORT_T;
typedef short *PSHORT_T;

typedef signed int INT_T;
typedef int *PINT_T;
typedef unsigned int UINT_T;
typedef unsigned int *PUINT_T;

typedef long LONG_T;
typedef unsigned long ULONG_T;
typedef long *PLONG_T;

typedef unsigned short WORD_T;
typedef WORD_T *PWORD_T;
typedef unsigned int DWORD_T;
typedef DWORD_T *PDWORD_T;

typedef float FLOAT_T;
typedef FLOAT_T *PFLOAT_T;

typedef long long DLONG_T;
typedef DLONG_T *PDLONG_T;

typedef unsigned long long DDWORD_T;
typedef DDWORD_T *PDDWORD_T;

typedef double DOUBLE_T;

typedef size_t SIZE_T;

#ifndef IN
#define IN 
#endif

#ifndef OUT
#define OUT
#endif


#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef INOUT
#define INOUT
#endif

#ifndef VOID
#define VOID void
#endif

#ifndef CONST
#define CONST const
#endif

#ifndef STATIC
#define STATIC static
#endif

#ifndef SIZEOF
#define SIZEOF sizeof
#endif

#ifndef INLINE
#define INLINE inline
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif  /* __PLATFORM_ADAPT_TYPE_H__ */