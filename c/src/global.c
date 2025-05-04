#include "include/global.h"

/* global variable definitions and initializations */
ErrorCode global_error_code = ERRORCODE_NO_ERROR;

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
