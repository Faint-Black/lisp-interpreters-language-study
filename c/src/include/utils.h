#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>
#include <stdio.h>

extern char* Dup_Str(const char* str);
extern int   Is_Valid_Lisp_Symbol_Character(char c);
extern void  Append_Char(char* c_arr, size_t* size, char c);
extern int   Has_Dot_Char(const char* str);
extern char  To_Uppercase(char c);

#endif /* UTILS_H */
