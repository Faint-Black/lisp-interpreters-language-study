/*******************************************************************************
 *
 *   +------+
 *   | MAIN | - entry point
 *   +------+
 *
 *  Codebase licensed under GPLv3, build instructions in README.
 *
 ******************************************************************************/

#include "include/atom.h"
#include "include/global.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/utils.h"
#include <stdio.h>
#include <stdlib.h>

/* TODO: global allocation pool */
/* TODO: dynamic arrays */
/* TODO: evaluator */

static void Cleanup_And_Exit(int exit_code, char* str, Token* tokens);

int main(void)
{
    char*  input_str;
    Token* lexed_token_array;
    Atom   parsed_atom;

    /* get input */
    input_str = Dup_Str("'(foo   ( + 42 69) )");

    /* lexing phase */
    lexed_token_array = Lex_Text(input_str);
    if (Get_Error())
    {
        sprintf(buffer, "lexing failed with error message \"%s\"", Get_Error());
        Fatal_Error_Msg(buffer);
        Cleanup_And_Exit(EXIT_FAILURE, input_str, lexed_token_array);
    }

    /* parsing phase */
    parsed_atom = Tokens_To_Sexpr(lexed_token_array);
    if (Get_Error())
    {
        sprintf(buffer, "parsing failed with error message \"%s\"", Get_Error());
        Fatal_Error_Msg(buffer);
        Cleanup_And_Exit(EXIT_FAILURE, input_str, lexed_token_array);
    }

    /* output phase */
    Bufprint_Token_Array(buffer, lexed_token_array);
    Log_Msg(buffer);
    Bufprint_Tree_Sexpr(buffer, parsed_atom);
    Log_Msg(buffer);
    Bufprint_Human_Sexpr(buffer, parsed_atom);
    Log_Msg(buffer);

    /* graciously exit */
    Cleanup_And_Exit(EXIT_SUCCESS, input_str, lexed_token_array);
    return 0;
}

static void Cleanup_And_Exit(int exit_code, char* str, Token* tokens)
{
    if (str != NULL)
    {
        free(str);
    }
    if (tokens != NULL)
    {
        Destroy_Token_Array(tokens);
    }

    exit(exit_code);
}
