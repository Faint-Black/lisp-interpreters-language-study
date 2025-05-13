#include "include/atom.h"
#include "include/global.h"
#include "include/utils.h"
#include <stdbool.h>
#include <stdio.h>

/* print one atom to stdout */
void Print_Atom(Atom atom)
{
    char buf[MAX_BUFFER_SIZE];
    switch (atom.type)
    {
    case ATOMTYPE_T:
        Log_Msg("ATOM: t");
        break;
    case ATOMTYPE_NIL:
        Log_Msg("ATOM: nil");
        break;
    case ATOMTYPE_INTEGER:
        sprintf(buf, "ATOM: integral %li", atom.value.integral);
        Log_Msg(buf);
        break;
    case ATOMTYPE_FLOAT:
        sprintf(buf, "ATOM: real %.4f", atom.value.floating);
        Log_Msg(buf);
        break;
    case ATOMTYPE_SYMBOL:
        sprintf(buf, "ATOM: symbol \"%s\"", atom.value.symbol);
        Log_Msg(buf);
        break;
    default:
        Error_Msg("ATOM: Printing of this type not implemented yet!");
        break;
    }
}

/* returns a boolean true atom */
Atom T_Atom(void)
{
    Atom result;
    result.type = ATOMTYPE_T;
    result.value.integral = 1;
    return result;
}

/* returns a boolean nil atom */
Atom Nil_Atom(void)
{
    Atom result;
    result.type = ATOMTYPE_NIL;
    result.value.integral = 0;
    return result;
}

/* returns an integral number atom */
Atom Int_Atom(long num)
{
    Atom result;
    result.type = ATOMTYPE_INTEGER;
    result.value.integral = num;
    return result;
}

/* returns a floating number atom */
Atom Float_Atom(float num)
{
    Atom result;
    result.type = ATOMTYPE_FLOAT;
    result.value.floating = num;
    return result;
}

/* copies the input identifier and returns the symbol atom */
Atom Symbol_Atom(const char* name)
{
    Atom result;
    result.type = ATOMTYPE_SYMBOL;
    result.value.symbol = Dup_Str(name);
    return result;
}
