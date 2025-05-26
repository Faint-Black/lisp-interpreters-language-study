#ifndef LISP_H
#define LISP_H
/*******************************************************************************
 *
 *   +------+
 *   | LISP | - header file
 *   +------+
 *
 *  Defines this Lisp implementation's builtin functions.
 *
 ******************************************************************************/

#include "atom.h"

/* list related functions */
extern Atom Lisp_Car(Atom atom);
extern Atom Lisp_Cdr(Atom atom);
extern Atom Lisp_Cons(Atom car, Atom cdr);

/* predicate functions */
extern Atom Lisp_Nullp(Atom atom);
extern Atom Lisp_Numberp(Atom atom);
extern Atom Lisp_Integralp(Atom atom);
extern Atom Lisp_Floatingp(Atom atom);
extern Atom Lisp_Symbolp(Atom atom);
extern Atom Lisp_Consp(Atom atom);

#endif /* LISP_H */
