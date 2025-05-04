#include "include/global.h"
#include <stdio.h>

/* global variable definitions and initializations */
ErrorCode global_error_code = ERRORCODE_NO_ERROR;

/* translation-unit local global variables */
const char* reset        = "\033[0m";
const char* black        = "\033[0;30m";
const char* red          = "\033[0;31m";
const char* green        = "\033[0;32m";
const char* yellow       = "\033[0;33m";
const char* blue         = "\033[0;34m";
const char* magenta      = "\033[0;35m";
const char* cyan         = "\033[0;36m";
const char* white        = "\033[0;37m";
const char* bold_black   = "\033[1;30m";
const char* bold_red     = "\033[1;31m";
const char* bold_green   = "\033[1;32m";
const char* bold_yellow  = "\033[1;33m";
const char* bold_blue    = "\033[1;34m";
const char* bold_magenta = "\033[1;35m";
const char* bold_cyan    = "\033[1;36m";
const char* bold_white   = "\033[1;37m";

/* returns the current error code */
ErrorCode Get_Error(void)
{
    return global_error_code;
}

/* sets the error to the input code */
void Set_Error(ErrorCode code)
{
    global_error_code = code;
}

/* display a buffered LOG message to stdout */
void Log_Msg(const char* msg)
{
    fprintf(stdout, "%sLOG%s: %s.\n", bold_blue, reset, msg);
}

/* display an unbuffered WARNING message to stderr */
void Warn_Msg(const char* msg)
{
    fprintf(stderr, "%sWARNING%s: %s.\n", bold_yellow, reset, msg);
}

/* display an unbuffered ERROR message to stderr */
void Error_Msg(const char* msg)
{
    fprintf(stderr, "%sERROR%s: %s.\n", red, reset, msg);
}

/* display an unbuffered FATAL ERROR message to stderr */
void Fatal_Error_Msg(const char* msg)
{
    fprintf(stderr, "%sFATAL%s: %s.\n", bold_red, reset, msg);
}
