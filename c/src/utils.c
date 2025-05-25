/*******************************************************************************
 *
 *   +-------+
 *   | UTILS | - translation unit file
 *   +-------+
 *
 *  Various helper functions that don't exactly fit being inside global.
 *
 ******************************************************************************/

#include "include/utils.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

enum ParenClass
{
    UNDEFINED = 0,
    ROUND,
    SQUARE,
    CURLY
};

/* duplicates a string into allocated memory */
char* Dup_Str(const char* str)
{
    char* result;
    if (str == NULL)
    {
        return NULL;
    }
    result = malloc((strlen(str) + 1) * sizeof(char));
    memcpy(result, str, (strlen(str) + 1));
    return result;
}

/* non allowed characters:
 * double quotes("), reserved for string literals
 * single quotes('), reserved for the quote operator
 * any parentheses or bracket
 * backslash(\), reserved for future use in special characters
 * dots(.) are allowed due to floating point literals, so they must
 * be manually handled to differentiate them from dotted pairs (car . cdr)
 */
int Is_Valid_Lisp_Symbol_Character(char c)
{
    return ((c == '!') || ((c >= 35) && (c <= 38)) || ((c >= 42) && (c <= 90))
            || ((c >= 94) && (c <= 122)));
}

/* appends char to a char buffer, automatically deals with the null terminator */
void Append_Char(char* c_arr, size_t* size, char c)
{
    c_arr[*size] = c;
    ++*size;
    c_arr[*size] = '\0';
}

/* checks if a string has a dot character */
int Has_Dot_Char(const char* str)
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

/* [a..z] -> [A..Z] */
char To_Uppercase(char c)
{
    if ((c >= 'a') && (c <= 'z'))
    {
        return (char)(c - 32);
    }
    return c;
}

/* returns true if all parentheses in the string are valid, returns false if not */
bool Check_Parentheses(const char* str)
{
    int             roundparen_count = 0;
    int             squareparen_count = 0;
    int             squigglyparen_count = 0;
    enum ParenClass opening_paren = UNDEFINED;
    enum ParenClass closing_paren = UNDEFINED;

    /* null pointer exception */
    if (!str)
    {
        return false;
    }

    while (*str)
    {
        switch (*str)
        {
        case '(':
            opening_paren = ROUND;
            roundparen_count++;
            break;
        case ')':
            closing_paren = ROUND;
            roundparen_count--;
            break;
        case '[':
            opening_paren = SQUARE;
            squareparen_count++;
            break;
        case ']':
            closing_paren = SQUARE;
            squareparen_count--;
            break;
        case '{':
            opening_paren = CURLY;
            squigglyparen_count++;
            break;
        case '}':
            closing_paren = CURLY;
            squigglyparen_count--;
            break;
        default:
            break;
        }

        /* if both opening and closing characters have been assigned */
        if ((opening_paren != UNDEFINED) && (closing_paren != UNDEFINED))
        {
            if (opening_paren == closing_paren)
            {
                opening_paren = UNDEFINED;
                closing_paren = UNDEFINED;
            }
            else
            {
                return false;
            }
        }

        str++;
    }

    /* all counters must equal zero at the end */
    if (!roundparen_count && !squareparen_count && !squigglyparen_count)
    {
        return true;
    }
    else
    {
        return false;
    }
}
