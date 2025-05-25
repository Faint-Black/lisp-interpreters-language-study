#ifndef EVAL_H
#define EVAL_H
/*******************************************************************************
 *
 *   +------+
 *   | EVAL | - header file
 *   +------+
 *
 *  Defines the primitive atom/list/s-expression Lisp data types and procedures,
 * as well as their printing.
 *
 ******************************************************************************/

#include "atom.h"

/* env related functions */
extern Atom Lisp_Eval(Atom expr);

#endif /* EVAL_H */
