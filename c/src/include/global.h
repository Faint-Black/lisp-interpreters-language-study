#ifndef GLOBAL_H
#define GLOBAL_H
/*******************************************************************************
 *
 *   +--------+
 *   | GLOBAL | - header file
 *   +--------+
 *
 *  Defines global functions, variables, typedefs and macros for use across all
 * source files on the project.
 *
 ******************************************************************************/

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

/* assert 64-bit CPU architecture */
#if !defined(ARCH_64)
#error "64-bit exclusive application!"
#endif

/* general-use constants */
#define PI       3.14159265358979323846L
#define EULER    2.71828L
#define THOUSAND 1000UL
#define MILLION  1000000UL
#define BILLION  1000000000UL
#define TRILLION 1000000000000UL

/* size related constants */
#define MAX_FILE_SIZE          (1 * MILLION)
#define MAX_LOCAL_BUFFER_SIZE  512
#define MAX_GLOBAL_BUFFER_SIZE 65536

/* global variables */
extern char        buffer[MAX_GLOBAL_BUFFER_SIZE];
extern const char* global_error_code;

/* global functions */
extern const char* Get_Error(void);
extern void        Set_Error(const char* msg);
extern void        Log_Msg(const char* msg);
extern void        Warn_Msg(const char* msg);
extern void        Error_Msg(const char* msg);
extern void        Fatal_Error_Msg(const char* msg);

#endif /* GLOBAL_H */
