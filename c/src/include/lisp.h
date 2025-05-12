#ifndef LISP_H
#define LISP_H

#include "atom.h"

extern Atom Lisp_Car(Atom atom);
extern Atom Lisp_Cdr(Atom atom);
extern Atom Lisp_Cons(Atom car, Atom cdr);
extern Atom Lisp_Nullp(Atom atom);

#endif /* LISP_H */
