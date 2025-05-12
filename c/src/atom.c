#include "include/atom.h"
#include "include/global.h"
#include "include/lisp.h"
#include "include/utils.h"
#include <stdbool.h>
#include <stdio.h>

/* print one atom to stdout */
void Print_Atom(Atom atom)
{
    switch (atom.type)
    {
    case ATOMTYPE_T:
        printf("t");
        break;
    case ATOMTYPE_NIL:
        printf("nil");
        break;
    case ATOMTYPE_INTEGER:
        printf("%li", atom.value.integral);
        break;
    case ATOMTYPE_FLOAT:
        printf("%.4f", atom.value.floating);
        break;
    case ATOMTYPE_SYMBOL:
        printf("%s", atom.value.symbol);
        break;
    case ATOMTYPE_PAIR:
        printf("(");
        Print_Atom(Lisp_Car(atom));
        printf(" . ");
        Print_Atom(Lisp_Cdr(atom));
        printf(")");
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
