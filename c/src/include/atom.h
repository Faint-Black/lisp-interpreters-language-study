#ifndef ATOM_H
#define ATOM_H
/*******************************************************************************
 *
 *   +------+
 *   | ATOM | - header file
 *   +------+
 *
 *  Defines the primitive atom/list/s-expression Lisp data types and procedures,
 * as well as their printing.
 *
 ******************************************************************************/

typedef enum AtomType
{
    ATOMTYPE_T,
    ATOMTYPE_NIL,
    ATOMTYPE_INTEGER,
    ATOMTYPE_FLOAT,
    ATOMTYPE_SYMBOL,
    ATOMTYPE_PAIR
} AtomType;

typedef struct Atom
{
    AtomType type;
    union
    {
        long         integral;
        float        floating;
        const char*  symbol;
        struct Cons* cons_cell;
    } value;
} Atom;

typedef struct Cons
{
    struct Atom atom[2];
} Pair;

extern void Bufprint_Tree_Sexpr(char* buf, Atom atom);
extern void Bufprint_Human_Sexpr(char* buf, Atom atom);
extern Atom Create_Atom_Copy(Atom atom);
extern Atom T_Atom(void);
extern Atom Nil_Atom(void);
extern Atom Int_Atom(long num);
extern Atom Float_Atom(float num);
extern Atom Symbol_Atom(const char* name);
extern Atom Boolean_To_Atom(int boolean);
extern int  Atom_To_Boolean(Atom atom);

#endif /* ATOM_H */
