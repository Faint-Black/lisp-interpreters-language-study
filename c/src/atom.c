/*******************************************************************************
 *
 *   +------+
 *   | ATOM | - translation unit file
 *   +------+
 *
 *  Defines the primitive atom/list/s-expression Lisp data types and procedures,
 * as well as their printing.
 *
 ******************************************************************************/

#include "include/atom.h"
#include "include/global.h"
#include "include/lisp.h"
#include "include/utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static void Recursive_Bufprint_Tree_Sexpr(int depth, char* buf, Atom atom);
static void Recursive_Bufprint_Expression(char* buf, Atom atom);
static void Recursive_Bufprint_List(char* buf, Atom atom);

/* logs all atoms onto a single string put at the input buf, in car/cdr tree form */
void Bufprint_Tree_Sexpr(char* buf, Atom atom)
{
    strncpy(buf, "Logging TREE S-EXPRESSIONS;\n", MAX_GLOBAL_BUFFER_SIZE);
    Recursive_Bufprint_Tree_Sexpr(0, buf, atom);
}

/* logs all atoms onto a single string put at the input buf, in humanly readable form */
void Bufprint_Human_Sexpr(char* buf, Atom atom)
{
    strncpy(buf, "Logging S-EXPRESSIONS;\n", MAX_GLOBAL_BUFFER_SIZE);
    Recursive_Bufprint_Expression(buf, atom);
    strncat(buf, "\n", MAX_GLOBAL_BUFFER_SIZE);
}

/* allocates contents of input atom into new returned atom */
Atom Create_Atom_Copy(Atom atom)
{
    /* TODO: be able to copy lists */
    Atom copy;
    copy.type = atom.type;

    switch (atom.type)
    {
    case ATOMTYPE_SYMBOL:
        copy.value.symbol = Dup_Str(atom.value.symbol);
        break;
    case ATOMTYPE_PAIR:
        Fatal_Error_Msg("cons cells atoms copy not implemented yet!");
        Set_Error("bad copy");
        copy = Nil_Atom();
        break;
    default:
        copy.value = atom.value;
        break;
    }

    return copy;
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

static void Recursive_Bufprint_Tree_Sexpr(int depth, char* buf, Atom atom)
{
    char temp_buf[MAX_LOCAL_BUFFER_SIZE];
    int  i;

    temp_buf[0] = '\0';
    for (i = 0; i < depth; i++)
    {
        temp_buf[i + 0] = '|';
        temp_buf[i + 1] = '-';
        temp_buf[i + 2] = ' ';
        temp_buf[i + 3] = '\0';
    }
    strncat(buf, temp_buf, MAX_GLOBAL_BUFFER_SIZE);

    switch (atom.type)
    {
    case ATOMTYPE_T:
        strncat(buf, "non-empty list (t)\n", MAX_GLOBAL_BUFFER_SIZE);
        break;
    case ATOMTYPE_NIL:
        strncat(buf, "empty list (nil)\n", MAX_GLOBAL_BUFFER_SIZE);
        break;
    case ATOMTYPE_INTEGER:
        sprintf(temp_buf, "integral (%li)\n", atom.value.integral);
        strncat(buf, temp_buf, MAX_GLOBAL_BUFFER_SIZE);
        break;
    case ATOMTYPE_FLOAT:
        sprintf(temp_buf, "real (%.4f)\n", atom.value.floating);
        strncat(buf, temp_buf, MAX_GLOBAL_BUFFER_SIZE);
        break;
    case ATOMTYPE_SYMBOL:
        sprintf(temp_buf, "symbol (\"%s\")\n", atom.value.symbol);
        strncat(buf, temp_buf, MAX_GLOBAL_BUFFER_SIZE);
        break;
    case ATOMTYPE_PAIR:
        strncat(buf, "PAIR\n", MAX_GLOBAL_BUFFER_SIZE);
        Recursive_Bufprint_Tree_Sexpr(depth + 1, buf, Lisp_Car(atom));
        Recursive_Bufprint_Tree_Sexpr(depth + 1, buf, Lisp_Cdr(atom));
        break;
    default:
        Set_Error("erroneous case caught");
        break;
    }
}

static void Recursive_Bufprint_Expression(char* buf, Atom atom)
{
    char temp_buf[MAX_LOCAL_BUFFER_SIZE];
    temp_buf[0] = '\0';

    switch (atom.type)
    {
    case ATOMTYPE_T:
        strncat(buf, "t", MAX_GLOBAL_BUFFER_SIZE);
        break;
    case ATOMTYPE_NIL:
        strncat(buf, "nil", MAX_GLOBAL_BUFFER_SIZE);
        break;
    case ATOMTYPE_INTEGER:
        sprintf(temp_buf, "%li", atom.value.integral);
        strncat(buf, temp_buf, MAX_GLOBAL_BUFFER_SIZE);
        break;
    case ATOMTYPE_FLOAT:
        sprintf(temp_buf, "%.4f", atom.value.floating);
        strncat(buf, temp_buf, MAX_GLOBAL_BUFFER_SIZE);
        break;
    case ATOMTYPE_SYMBOL:
        sprintf(temp_buf, "%s", atom.value.symbol);
        strncat(buf, temp_buf, MAX_GLOBAL_BUFFER_SIZE);
        break;
    case ATOMTYPE_PAIR:
        strncat(buf, "(", MAX_GLOBAL_BUFFER_SIZE);
        Recursive_Bufprint_List(buf, atom);
        strncat(buf, ")", MAX_GLOBAL_BUFFER_SIZE);
        break;
    default:
        Set_Error("erroneous case caught");
        break;
    }
}

static void Recursive_Bufprint_List(char* buf, Atom atom)
{
    Atom car = Lisp_Car(atom);
    Atom cdr = Lisp_Cdr(atom);

    Recursive_Bufprint_Expression(buf, car);
    if (cdr.type == ATOMTYPE_PAIR)
    {
        strncat(buf, " ", MAX_GLOBAL_BUFFER_SIZE);
        Recursive_Bufprint_List(buf, cdr);
    }
    else if (cdr.type == ATOMTYPE_NIL)
    {
        return;
    }
    else
    {
        strncat(buf, " . ", MAX_GLOBAL_BUFFER_SIZE);
        Recursive_Bufprint_Expression(buf, cdr);
    }
}
