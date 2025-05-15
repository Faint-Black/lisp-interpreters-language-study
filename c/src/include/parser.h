#ifndef PARSER_H
#define PARSER_H
/*******************************************************************************
 *
 *   +--------+
 *   | PARSER | - header file
 *   +--------+
 *
 *  Responsible for turning the lexed tokens into *unevaluated* Lisp
 * S-Expressions.
 *
 ******************************************************************************/

#include "atom.h"
#include "lexer.h"

extern Atom Tokens_To_Sexpr(Token* tk_arr);

#endif /* PARSER_H */
