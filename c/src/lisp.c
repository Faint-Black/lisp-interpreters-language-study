#include "include/lisp.h"
#include "include/atom.h"
#include <stdlib.h>

static Atom* Car(Atom atom);
static Atom* Cdr(Atom atom);

/* returns the car of a pair */
Atom Lisp_Car(Atom atom)
{
    return atom.value.pair->atom[0];
}

/* returns the cdr of a pair */
Atom Lisp_Cdr(Atom atom)
{
    return atom.value.pair->atom[1];
}

/* returns a constructed list */
Atom Lisp_Cons(Atom car, Atom cdr)
{
    Atom result;
    result.type = ATOMTYPE_PAIR;
    /* TODO: deallocate when done */
    result.value.pair = malloc(sizeof(Pair));
    *Car(result) = car;
    *Cdr(result) = cdr;
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

/* returns address of the pair's car */
static Atom* Car(Atom atom)
{
    return &atom.value.pair->atom[0];
}

/* returns address of the pair's car */
static Atom* Cdr(Atom atom)
{
    return &atom.value.pair->atom[1];
}
