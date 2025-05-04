#include "include/global.h"

/* assert 64-bit CPU */
#if !defined(ARCH_64)
#error "64-bit exclusive application!"
#endif

int main(void)
{
    Log_Msg("this is a log");
    Warn_Msg("this is a warning");
    Error_Msg("this is an error");
    Fatal_Error_Msg("this is a fatal error");
    return 0;
}
