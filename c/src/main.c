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
#include "include/eval.h"
#include "include/global.h"
#include "include/lexer.h"
#include "include/lisp.h"
#include "include/parser.h"
#include "include/utils.h"
#include <stdio.h>
#include <stdlib.h>

/* TODO: support for multiple sexprs */
/* TODO: global allocation pool */
/* TODO: dynamic arrays */
/* TODO: evaluator */

static void Cleanup_And_Exit(int exit_code, char* str, Token* tokens);

int main(void)
{
    char*  input_str;
    Token* lexed_token_array;
    Atom   parsed_expression;
    Atom   evaluated_result;

    /* input phase */
    input_str = Dup_Str("(+ 1 2)");

    /* lexing phase */
    lexed_token_array = Lex_Text(input_str);
    if (Get_Error())
    {
        sprintf(buffer, "lexing failed with error message \"%s\"", Get_Error());
        Fatal_Error_Msg(buffer);
        Cleanup_And_Exit(EXIT_FAILURE, input_str, lexed_token_array);
    }
    Bufprint_Token_Array(buffer, lexed_token_array);
    Log_Msg(buffer);

    /* parsing phase */
    parsed_expression = Tokens_To_Sexpr(lexed_token_array);
    if (Get_Error())
    {
        sprintf(buffer, "parsing failed with error message \"%s\"", Get_Error());
        Fatal_Error_Msg(buffer);
        Cleanup_And_Exit(EXIT_FAILURE, input_str, lexed_token_array);
    }
    Bufprint_Tree_Sexpr(buffer, parsed_expression);
    Log_Msg(buffer);
    Bufprint_Human_Sexpr(buffer, parsed_expression);
    Log_Msg(buffer);

    /* evaluation phase */
    evaluated_result = Lisp_Eval(parsed_expression);
    Bufprint_Human_Sexpr(buffer, evaluated_result);
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
