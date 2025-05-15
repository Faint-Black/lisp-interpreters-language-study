#ifndef ATOM_H
#define ATOM_H

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

extern void Bufprint_Sexpr(char* buf, Atom atom);
extern Atom Create_Atom_Copy(Atom atom);
extern Atom T_Atom(void);
extern Atom Nil_Atom(void);
extern Atom Int_Atom(long num);
extern Atom Float_Atom(float num);
extern Atom Symbol_Atom(const char* name);

#endif /* ATOM_H */
