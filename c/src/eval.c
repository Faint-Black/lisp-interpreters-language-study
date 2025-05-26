/*******************************************************************************
 *
 *   +------+
 *   | EVAL | - translation unit file
 *   +------+
 *
 *  Defines the Lisp evaluator function and the environment.
 *
 ******************************************************************************/

#include "include/eval.h"
#include "include/atom.h"
#include "include/lisp.h"

/* TODO: friggin' everything */
/* watch https://youtu.be/f13dTrBHDqY */

Atom Lisp_Eval(Atom expr)
{
    /* numbers evaluate to themselves */
    if (Atom_To_Boolean(Lisp_Numberp(expr)))
    {
        return expr;
    }

    return Nil_Atom();
}
