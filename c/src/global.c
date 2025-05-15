/*******************************************************************************
 *
 *   +--------+
 *   | GLOBAL | - translation unit file
 *   +--------+
 *
 *  Defines global functions, variables, typedefs and macros for use across all
 * source files on the project.
 *
 ******************************************************************************/

#include "include/global.h"
#include <stdio.h>

/* global variable definitions and initializations */
char        buffer[MAX_GLOBAL_BUFFER_SIZE];
const char* global_error_code = NULL;

/* translation-unit local global variables */
#ifdef OS_LINUX
const char* reset = "\033[0m";
const char* black = "\033[0;30m";
const char* red = "\033[0;31m";
const char* green = "\033[0;32m";
const char* yellow = "\033[0;33m";
const char* blue = "\033[0;34m";
const char* magenta = "\033[0;35m";
const char* cyan = "\033[0;36m";
const char* white = "\033[0;37m";
const char* bold_black = "\033[1;30m";
const char* bold_red = "\033[1;31m";
const char* bold_green = "\033[1;32m";
const char* bold_yellow = "\033[1;33m";
const char* bold_blue = "\033[1;34m";
const char* bold_magenta = "\033[1;35m";
const char* bold_cyan = "\033[1;36m";
const char* bold_white = "\033[1;37m";
#endif

/* returns the current error code */
const char* Get_Error(void)
{
    return global_error_code;
}

/* sets the error to the input code */
void Set_Error(const char* msg)
{
    global_error_code = msg;
}

/* display a buffered LOG message to stdout */
void Log_Msg(const char* msg)
{
#ifdef OS_LINUX
    fprintf(stdout, "%sLOG%s: %s\n", bold_blue, reset, msg);
#else
    fprintf(stdout, "LOG: %s\n", msg);
#endif
}

/* display an unbuffered WARNING message to stderr */
void Warn_Msg(const char* msg)
{
#ifdef OS_LINUX
    fprintf(stderr, "%sWARNING%s: %s\n", bold_yellow, reset, msg);
#else
    fprintf(stderr, "WARNING: %s\n", msg);
#endif
}

/* display an unbuffered ERROR message to stderr */
void Error_Msg(const char* msg)
{
#ifdef OS_LINUX
    fprintf(stderr, "%sERROR%s: %s\n", red, reset, msg);
#else
    fprintf(stderr, "ERROR: %s\n", msg);
#endif
}

/* display an unbuffered FATAL ERROR message to stderr */
void Fatal_Error_Msg(const char* msg)
{
#ifdef OS_LINUX
    fprintf(stderr, "%sFATAL%s: %s\n", bold_red, reset, msg);
#else
    fprintf(stderr, "FATAL: %s\n", msg);
#endif
}
