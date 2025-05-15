#include "include/atom.h"
#include "include/global.h"
#include "include/lexer.h"
#include "include/parser.h"
#include <stdio.h>

/* TODO: dynamic arrays */
/* TODO: abstract syntax tree */
/* TODO: evaluator */

/* TODO: S-Expression are ALREADY implemented!
 *       i just need to finalize the list recursive parsing functions
 */

/* TODO: Print_Fn -> Get_Str_Fn */

int main(void)
{
    const char* input_str;
    Token*      lexed_token_array;
    Atom        parsed_atom;

    input_str = "(+ (* 1 5) 2)";

    /* lexing phase */
    lexed_token_array = Lex_Text(input_str);
    if (Get_Error())
    {
        sprintf(buffer, "lexing failed with error message \"%s\"", Get_Error());
        Fatal_Error_Msg(buffer);
    }

    /* parsing phase */
    parsed_atom = Tokens_To_Sexpr(lexed_token_array);
    if (Get_Error())
    {
        sprintf(buffer, "parsing failed with error message \"%s\"", Get_Error());
        Fatal_Error_Msg(buffer);
    }

    /* output phase */
    Bufprint_Token_Array(buffer, lexed_token_array);
    Log_Msg(buffer);
    Bufprint_Sexpr(buffer, parsed_atom);
    Log_Msg(buffer);

    /* cleanup phase */
    Destroy_Token_Array(lexed_token_array);

    return 0;
}
