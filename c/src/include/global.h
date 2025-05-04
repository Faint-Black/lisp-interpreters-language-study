#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdbool.h>

/* detect operating system */
#if defined(_WIN32) || defined(_WIN64)
#define OS_WINDOWS
#elif defined(__linux__)
#define OS_LINUX
#elif defined(__APPLE__) || defined(__MACH__)
#define OS_MACOS
#elif defined(__unix__)
#define OS_UNIX
#elif defined(__FreeBSD__)
#define OS_FREEBSD
#elif defined(__ANDROID__)
#define OS_ANDROID
#elif defined(__CYGWIN__)
#define OS_CYGWIN
#else
#define OS_UNKNOWN
#endif

/* detect architecture (32 or 64 bits) */
#if (__SIZEOF_POINTER__ == 8)
#define ARCH_64
#elif (__SIZEOF_POINTER__ == 4)
#define ARCH_32
#else
#define ARCH_UNKNOWN
#endif

/* general-use constants */
#define PI       3.14159265358979323846L
#define EULER    2.71828L
#define THOUSAND 1000UL
#define MILLION  1000000UL
#define BILLION  1000000000UL
#define TRILLION 1000000000000UL

/* size related constants */
#define MAX_FILE_SIZE   (1 * MILLION)
#define MAX_BUFFER_SIZE 512

/* typedefs */
typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned int   dword;
typedef unsigned long  qword;
typedef unsigned long  size_t;
typedef enum
{
    ERRORCODE_NO_ERROR = 0, /* no current error in effect */
    ERRORCODE_GENERAL_ERROR /* error with no further description */
} ErrorCode;

/* global variables */
extern ErrorCode global_error_code;

/* global functions */
extern ErrorCode Get_Error(void);
extern void      Set_Error(ErrorCode code);

#endif /* GLOBAL_H */
