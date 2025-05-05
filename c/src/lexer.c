#include "include/lexer.h"
#include "include/global.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* translation-unit local functions */
static Token Undefined_Token(void);
static Token Symbol_Token(const char* str);
static Token Paren_Token(char paren, unsigned int depth);
static Token EOF_Token(void);
static Token Dot_Token(void);
static Token Quote_Token(void);
static Token Int_Token(long num);
static Token Float_Token(float num);
static Token String_To_Token(const char* str);
static void  Destroy_Token(Token tk);
static void  Append_Token(Token* tk_arr, size_t* size, Token tk);
static void  Append_Char(char* c_arr, size_t* size, char c);
static int   Has_Dot_Char(const char* str);

Token* Lex_Text(const char* str)
{
    Token*       result;
    Token        token_buf[MAX_BUFFER_SIZE];
    char         string_buf[MAX_BUFFER_SIZE];
    size_t       token_bufsize;
    size_t       string_bufsize;
    unsigned int paren_depth;
    char         c;
    size_t       i;

    if (str == NULL)
    {
        Set_Error("null input string");
        return NULL;
    }

    /* init string buffer as an empty string */
    string_buf[0] = '\0';
    string_bufsize = 0;
    /* init token buffer as an empty array */
    token_buf[0] = Undefined_Token();
    token_bufsize = 0;
    /* init parenthesis depth variable */
    paren_depth = 0;

    /* main parsing loop */
    for (i = 0; i < strlen(str); i++)
    {
        c = str[i];

        /* very liberal when it comes to naming symbols */
        if (Is_Valid_Lisp_Symbol_Character(c))
        {
            Append_Char(string_buf, &string_bufsize, c);
        }
        /* flush finished string into token, then reset buffer */
        else if (string_bufsize > 0)
        {
            Append_Token(token_buf, &token_bufsize, String_To_Token(string_buf));
            string_buf[0] = '\0';
            string_bufsize = 0;
        }

        /* opening parentheses */
        if (c == '(')
        {
            Append_Token(token_buf, &token_bufsize, Paren_Token('(', paren_depth));
            paren_depth++;
        }
        /* closing parentheses */
        if (c == ')')
        {
            paren_depth--;
            Append_Token(token_buf, &token_bufsize, Paren_Token(')', paren_depth));
        }
        /* builtin lisp quote function */
        if (c == '\'')
        {
            Append_Token(token_buf, &token_bufsize, Quote_Token());
        }
    }

    /* allocate and copy buffer */
    Append_Token(token_buf, &token_bufsize, EOF_Token());
    result = (Token*)malloc(token_bufsize * sizeof(Token));
    memcpy(result, token_buf, token_bufsize * sizeof(Token));
    return result;
}

/* deallocate contents of all tokens in an EOF terminated token array */
void Destroy_Token_Array(Token* tk_arr)
{
    int i = 0;
    if (tk_arr == NULL)
    {
        return;
    }
    while (true)
    {
        if (tk_arr[i].type == PTT_EOF)
        {
            break;
        }
        else
        {
            Destroy_Token(tk_arr[i]);
        }
        i++;
    }
}

/* logs all individual tokens and their contents */
void Print_Token_Array(Token* tk_arr)
{
    char buf[MAX_BUFFER_SIZE];
    int  i = 0;
    bool quit = false;
    if (tk_arr == NULL)
    {
        return;
    }
    while (!quit)
    {
        switch (tk_arr[i].type)
        {
        case PTT_UNDEFINED:
            Log_Msg("Undefined token, aborting print.");
            quit = true;
            break;
        case PTT_L_PAREN:
            sprintf(buf, "'(' of depth %li", tk_arr[i].value.integral);
            Log_Msg(buf);
            break;
        case PTT_R_PAREN:
            sprintf(buf, "')' of depth %li", tk_arr[i].value.integral);
            Log_Msg(buf);
            break;
        case PTT_DOT:
            Log_Msg("Dot token");
            break;
        case PTT_QUOTE:
            Log_Msg("Quote token");
            break;
        case PTT_SYMBOL:
            sprintf(buf, "Symbol token \"%s\"", tk_arr[i].value.symbol);
            Log_Msg(buf);
            break;
        case PTT_LITERAL_INTEGRAL_NUM:
            sprintf(buf, "Integer token of value %li", tk_arr[i].value.integral);
            Log_Msg(buf);
            break;
        case PTT_LITERAL_FLOATING_NUM:
            sprintf(buf, "Floating token of value %f", tk_arr[i].value.floating);
            Log_Msg(buf);
            break;
        case PTT_EOF:
            Log_Msg("EOF token");
            quit = true;
            break;
        default:
            Log_Msg("Unknown token, aborting print.");
            quit = true;
            break;
        }
        i++;
    }
}

/* default init token */
static Token Undefined_Token(void)
{
    Token result;
    result.type = PTT_UNDEFINED;
    result.value.integral = -1;
    return result;
}

/* allocates a copy of the input and returns the symbol token struct */
static Token Symbol_Token(const char* str)
{
    Token result;

    /* str length limited to the buffer max size */
    char* dup = NULL;
    char  buf[MAX_BUFFER_SIZE];
    /* copy input string into fixed size buffer */
    strncpy(buf, str, MAX_BUFFER_SIZE);
    buf[MAX_BUFFER_SIZE - 1] = '\0';
    /* create an allocated duplicate of the buffer contents */
    dup = malloc((strlen(buf) + 1) * sizeof(char));
    memcpy(dup, buf, (strlen(buf) + 1));

    result.type = PTT_SYMBOL;
    result.value.symbol = dup;
    return result;
}

/* paren can be either '(' or ')', depth represents level of depth of the parentheses */
static Token Paren_Token(char paren, unsigned int depth)
{
    Token result;
    if (paren == '(')
    {
        result.type = PTT_L_PAREN;
    }
    else
    {
        result.type = PTT_R_PAREN;
    }
    result.value.integral = depth;
    return result;
}

/* returns an EOF token */
static Token EOF_Token(void)
{
    Token result;
    result.type = PTT_EOF;
    result.value.integral = 0;
    return result;
}

/* returns a DOT token */
static Token Dot_Token(void)
{
    Token result;
    result.type = PTT_DOT;
    result.value.integral = 0;
    return result;
}

/* returns a QUOTE token */
static Token Quote_Token(void)
{
    Token result;
    result.type = PTT_QUOTE;
    result.value.integral = 0;
    return result;
}

/* returns an INTEGRAL token, with the given input value */
static Token Int_Token(long num)
{
    Token result;
    result.type = PTT_LITERAL_INTEGRAL_NUM;
    result.value.integral = num;
    return result;
}

/* returns a FLOATING token, with the given input value */
static Token Float_Token(float num)
{
    Token result;
    result.type = PTT_LITERAL_FLOATING_NUM;
    result.value.floating = num;
    return result;
}

/* decides how to interpret a string into a token, examples:
 * "." -> dot operator token.
 * "42" -> integer literal 42 token.
 * "4.2" -> floating literal 4.2 token.
 * "foo" -> symbol with text "foo".
 */
static Token String_To_Token(const char* str)
{
    long  integral_num;
    float floating_num;
    int   has_dot = Has_Dot_Char(str);

    if (!strcmp(str, "."))
    {
        return Dot_Token();
    }
    else if ((has_dot == true) && (sscanf(str, "%f", &floating_num) == 1))
    {
        return Float_Token(floating_num);
    }
    else if ((has_dot == false) && (sscanf(str, "%li", &integral_num) == 1))
    {
        return Int_Token(integral_num);
    }
    else
    {
        return Symbol_Token(str);
    }
}

/* frees allocated memory inside Token struct */
static void Destroy_Token(Token tk)
{
    if (tk.type == PTT_SYMBOL)
    {
        free(tk.value.symbol);
    }
}

/* appends token to a token array, then increments the size counter */
static void Append_Token(Token* tk_arr, size_t* size, Token tk)
{
    tk_arr[*size] = tk;
    ++*size;
}

/* appends char to a char buffer, automatically deals with the null terminator */
static void Append_Char(char* c_arr, size_t* size, char c)
{
    c_arr[*size] = c;
    ++*size;
    c_arr[*size] = '\0';
}

/* checks if a string has a dot character,
 * used to determine if a number is a float or int
 */
static int Has_Dot_Char(const char* str)
{
    while (*str)
    {
        if ((*str) == '.')
        {
            return true;
        }
        str++;
    }
    return false;
}
