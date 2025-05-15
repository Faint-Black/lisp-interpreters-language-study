/*******************************************************************************
 *
 *   +--------+
 *   | PARSER | - translation unit file
 *   +--------+
 *
 *  Responsible for turning the lexed tokens into *unevaluated* Lisp
 * S-Expressions.
 *
 ******************************************************************************/

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

/* primitive parsing operations */
static Token Peek(Token* tokens, size_t size);
static Token Consume(Token* tokens, size_t* size);
static bool  Match(Token* tokens, size_t* size, TokenType target);

/* TODO: A proper lisp program may contain multiple s-exprs,
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
        /* details above the function's definition */
        Consume(tokens, counter);
        return Parse_Quote(tokens, counter);
        break;
    case PTT_L_PAREN:
        /* consume '(', then parse and return right expression */
        Consume(tokens, counter);
        return Parse_List(tokens, counter);
        break;
    case PTT_SYMBOL:
        /* consume and return 'foo' */
        Consume(tokens, counter);
        return Symbol_Atom(current_token.value.symbol);
        break;
    case PTT_TRUE:
        /* consume and return 't' */
        Consume(tokens, counter);
        return T_Atom();
        break;
    case PTT_FALSE:
        /* consume and return 'nil' */
        Consume(tokens, counter);
        return Nil_Atom();
        break;
    case PTT_LITERAL_INTEGRAL_NUM:
        /* consume and return '42' */
        Consume(tokens, counter);
        return Int_Atom(current_token.value.integral);
        break;
    case PTT_LITERAL_FLOATING_NUM:
        /* consume and return '1337.42' */
        Consume(tokens, counter);
        return Float_Atom(current_token.value.floating);
        break;
    case PTT_R_PAREN:
        /* all ')' are supposed to be consumed at the list parsers */
        Set_Error("caught closing parenthesis during parsing");
        return Nil_Atom();
        break;
    default:
        Set_Error("unknown token");
        return Nil_Atom();
        break;
    }
}

/* syntatic sugar for turning 'A into (quote A) */
static Atom Parse_Quote(Token* tokens, size_t* counter)
{
    Atom quote_atom = Symbol_Atom("quote");
    Atom right_expression = Parse_Expression(tokens, counter);
    return Lisp_Cons(quote_atom, Lisp_Cons(right_expression, Nil_Atom()));
}

/* recursively goes through parenthesis lists and dotted pairs */
static Atom Parse_List(Token* tokens, size_t* counter)
{
    Atom car;
    Atom cdr;

    /* (A B C) => [A]->[B]->[C]->nil */
    if (Match(tokens, counter, PTT_R_PAREN))
    {
        return Nil_Atom();
    }

    /* (A . (B . (C . nil))) */
    car = Parse_Expression(tokens, counter);
    if (Match(tokens, counter, PTT_DOT))
    {
        cdr = Parse_Expression(tokens, counter);
        if (Match(tokens, counter, PTT_R_PAREN) == false)
        {
            Set_Error("expected ')' after dotted pair");
            return Nil_Atom();
        }
        return Lisp_Cons(car, cdr);
    }

    /* (A B C D ...) */
    cdr = Parse_List(tokens, counter);
    return Lisp_Cons(car, cdr);
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
