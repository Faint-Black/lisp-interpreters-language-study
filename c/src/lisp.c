#include "include/lisp.h"
#include "include/atom.h"
#include <stdlib.h>

static Atom* Internal_CAR(Atom atom);
static Atom* Internal_CDR(Atom atom);

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
    *Internal_CAR(result) = car;
    *Internal_CDR(result) = cdr;
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

/* returns address of the cons cell's car */
static Atom* Internal_CAR(Atom atom)
{
    return &atom.value.cons_cell->atom[0];
}

/* returns address of the cons cell's cdr */
static Atom* Internal_CDR(Atom atom)
{
    return &atom.value.cons_cell->atom[1];
}
