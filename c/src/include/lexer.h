#ifndef LEXER_H
#define LEXER_H

typedef enum TokenType
{
    PTT_UNDEFINED = 0,        /* default init value */
    PTT_L_PAREN,              /* '(' */
    PTT_R_PAREN,              /* ')' */
    PTT_DOT,                  /* (foo . bar) */
    PTT_QUOTE,                /* '(foo) */
    PTT_SYMBOL,               /* foo */
    PTT_LITERAL_INTEGRAL_NUM, /* 42 */
    PTT_LITERAL_FLOATING_NUM, /* 4.2 */
    PTT_EOF                   /* End Of File */
} TokenType;

typedef struct Token
{
    TokenType type;
    union
    {
        long  integral;
        float floating;
        char* symbol;
    } value;
} Token;

extern Token* Lex_Text(const char* str);
extern void   Destroy_Token_Array(Token* tk_arr);
extern void   Print_Token_Array(Token* tk_arr);

#endif /* LEXER_H */
