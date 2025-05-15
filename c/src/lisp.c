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
    if (atom.type == ATOMTYPE_NIL)
    {
        return T_Atom();
    }
    else
    {
        return Nil_Atom();
    }
}
