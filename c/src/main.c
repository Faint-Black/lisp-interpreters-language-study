#include "include/global.h"
#include "include/lexer.h"
#include <stdio.h>

/* assert 64-bit CPU */
#if !defined(ARCH_64)
#error "64-bit exclusive application!"
#endif

/* TODO: dynamic arrays */
/* TODO: abstract syntax tree */
/* TODO: evaluator */

int main(void)
{
    const char* input_str;
    char        buf[MAX_BUFFER_SIZE];
    Token*      lexed_token_array;

    input_str = "(if (eql (+ 20 22) 69)\n"
                "    t\n"
                "  nil)\n";

    lexed_token_array = Lex_Text(input_str);
    if (lexed_token_array == NULL)
    {
        sprintf(buf, "lexing failed with error message \"%s\"", Get_Error());
        Fatal_Error_Msg(buf);
    }
    Print_Token_Array(lexed_token_array);
    Destroy_Token_Array(lexed_token_array);

    return 0;
}
