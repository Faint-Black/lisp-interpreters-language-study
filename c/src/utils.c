#include "include/utils.h"

/* non allowed characters:
 * double quotes("), single quotes('), any parentheses or bracket, and backslash(\)
 * dots must be manually handled as for fractional numbers and (car . cdr)
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
