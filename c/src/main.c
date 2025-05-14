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
    char        buf[MAX_BUFFER_SIZE];
    Token*      lexed_token_array;
    Atom        parsed_atom;

    input_str = "1337.42";

    /* lexing phase */
    lexed_token_array = Lex_Text(input_str);
    if (Get_Error())
    {
        sprintf(buf, "lexing failed with error message \"%s\"", Get_Error());
        Fatal_Error_Msg(buf);
    }

    /* parsing phase */
    parsed_atom = Tokens_To_Atom(lexed_token_array);
    if (Get_Error())
    {
        sprintf(buf, "parsing failed with error message \"%s\"", Get_Error());
        Fatal_Error_Msg(buf);
    }

    /* output phase */
    Print_Token_Array(lexed_token_array);
    Print_Atom(parsed_atom);
    printf("\n");

    /* cleanup phase */
    Destroy_Token_Array(lexed_token_array);

    return 0;
}
