/*******************************************************************************
 *
 *   +------+
 *   | LISP | - translation unit file
 *   +------+
 *
 *  Defines this Lisp implementation's builtin functions.
 *
 ******************************************************************************/

#include "include/lisp.h"
#include "include/atom.h"
#include <stdlib.h>

/* returns the car of a pair */
Atom Lisp_Car(Atom atom)
{
    return atom.value.cons_cell->atom[0];
}

/* returns the cdr of a pair */
Atom Lisp_Cdr(Atom atom)
{
    return atom.value.cons_cell->atom[1];
}

/* returns a constructed list */
Atom Lisp_Cons(Atom car, Atom cdr)
{
    Atom result;
    result.type = ATOMTYPE_PAIR;
    /* TODO: deallocate when done */
    result.value.cons_cell = malloc(sizeof(Pair));
    result.value.cons_cell->atom[0] = car;
    result.value.cons_cell->atom[1] = cdr;
    return result;
}

/* returns T if an atom is null, NIL if not */
Atom Lisp_Nullp(Atom atom)
{
    return Boolean_To_Atom(atom.type == ATOMTYPE_NIL);
}

/* returns T if an atom is FOO, NIL if not */
Atom Lisp_Numberp(Atom atom)
{
    return Boolean_To_Atom((atom.type == ATOMTYPE_INTEGER) || (atom.type == ATOMTYPE_FLOAT));
}

/* returns T if an atom is FOO, NIL if not */
Atom Lisp_Integralp(Atom atom)
{
    return Boolean_To_Atom(atom.type == ATOMTYPE_INTEGER);
}

/* returns T if an atom is FOO, NIL if not */
Atom Lisp_Floatingp(Atom atom)
{
    return Boolean_To_Atom(atom.type == ATOMTYPE_FLOAT);
}

/* returns T if an atom is FOO, NIL if not */
Atom Lisp_Symbolp(Atom atom)
{
    return Boolean_To_Atom(atom.type == ATOMTYPE_SYMBOL);
}

/* returns T if an atom is FOO, NIL if not */
Atom Lisp_Consp(Atom atom)
{
    return Boolean_To_Atom(atom.type == ATOMTYPE_PAIR);
}
