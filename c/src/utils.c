#include "include/utils.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

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

/* [a..z] -> [A..Z] */
char To_Uppercase(char c)
{
    if ((c >= 'a') && (c <= 'z'))
    {
        return (char)(c - 32);
    }
    else
    {
        return c;
    }
}
