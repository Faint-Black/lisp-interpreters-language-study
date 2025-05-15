#include "include/parser.h"
#include "include/atom.h"
#include "include/global.h"
#include "include/lexer.h"
#include "include/lisp.h"
#include <stdbool.h>
#include <stdio.h>

/* recursive parsing functions */
static Atom Parse_Expression(Token* tokens, size_t* counter);
static Atom Parse_Quote(Token* tokens, size_t* counter);
static Atom Parse_List(Token* tokens, size_t* counter);
static Atom Parse_Dotted_Pair(Token* tokens, size_t* counter);

/* primitive parsing operations */
static Token Peek(Token* tokens, size_t size);
static Token Consume(Token* tokens, size_t* size);
static bool  Match(Token* tokens, size_t* size, TokenType target);

/* quick helper functions */
static void Append_Atom(Atom* atom_arr, size_t* size, Atom atom);

/* TODO: A proper lisp program may contain multiple sexprs,
 * for example:
 *
 * (setq x 42)         ; sexpr #1
 * (setq y 69)         ; sexpr #2
 * (* (+ x 1) (- y 1)) ; sexpr #3
 *
 * A plural return must be implemented later
 */
/* returns the parsed s-expression (singular) */
Atom Tokens_To_Sexpr(Token* tk_arr)
{
    Atom   result;
    size_t token_index = 0;

    result = Parse_Expression(tk_arr, &token_index);

    return result;
}

/* recursive parser */
static Atom Parse_Expression(Token* tokens, size_t* counter)
{
    Token current_token = Peek(tokens, *counter);
    switch (current_token.type)
    {
    case PTT_QUOTE:
        Consume(tokens, counter);
        return Parse_Quote(tokens, counter);
        break;
    case PTT_DOT:
        Consume(tokens, counter);
        return Parse_Dotted_Pair(tokens, counter);
        break;
    case PTT_L_PAREN:
        Consume(tokens, counter);
        return Parse_List(tokens, counter);
        break;
    case PTT_SYMBOL:
        Consume(tokens, counter);
        return Symbol_Atom(current_token.value.symbol);
        break;
    case PTT_TRUE:
        Consume(tokens, counter);
        return T_Atom();
        break;
    case PTT_FALSE:
        Consume(tokens, counter);
        return Nil_Atom();
        break;
    case PTT_LITERAL_INTEGRAL_NUM:
        Consume(tokens, counter);
        return Int_Atom(current_token.value.integral);
        break;
    case PTT_LITERAL_FLOATING_NUM:
        Consume(tokens, counter);
        return Float_Atom(current_token.value.floating);
        break;
    default:
        Set_Error("unknown token");
        return Nil_Atom();
        break;
    }
}

/* TODO */
static Atom Parse_Quote(Token* tokens, size_t* counter)
{
    Fatal_Error_Msg("not implemented yet");
    Consume(tokens, counter);
    return Int_Atom(42);
}

/* recursively goes through parenthesis contained tokens */
/* ( + 1 2 ) */
/* [+]-> [1]-> [2]-> nil */
static Atom Parse_List(Token* tokens, size_t* counter)
{
    Atom car;
    Atom cdr;

    if (Match(tokens, counter, PTT_R_PAREN))
    {
        return Nil_Atom();
    }

    car = Parse_Expression(tokens, counter);
    cdr = Parse_List(tokens, counter);

    return Lisp_Cons(car, cdr);
}

/* TODO */
static Atom Parse_Dotted_Pair(Token* tokens, size_t* counter)
{
    Fatal_Error_Msg("not implemented yet");
    Consume(tokens, counter);
    return Int_Atom(42);
}

/* return current token without incrementing the counter */
static Token Peek(Token* tokens, size_t size)
{
    return tokens[size];
}

/* return current token, then increment counter */
static Token Consume(Token* tokens, size_t* size)
{
    ++*size;
    return tokens[(*size) - 1];
}

/* checks and consumes the current token if it is of a certain type */
static bool Match(Token* tokens, size_t* size, TokenType target)
{
    Token current_token = Peek(tokens, *size);
    if (current_token.type == target)
    {
        Consume(tokens, size);
        return true;
    }
    return false;
}

/* appends an atom to an atom array, then increments the size counter */
static void Append_Atom(Atom* atom_arr, size_t* size, Atom atom)
{
    atom_arr[*size] = atom;
    ++*size;
}
