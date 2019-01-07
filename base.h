#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BASE_H
#define BASE_H

enum {CONS, ATOM, OBJECT};
enum {OBJ_INTEGER, OBJ_REAL, OBJ_STRING, OBJ_ATOM, OBJ_LIST};

typedef struct cell {
	int          kind;
	struct cell *head;
	struct cell *tail;
} Cell;

typedef struct obj {
	int          kind;
	int          bound;
	void        *value;
} Object;

Cell *cons(Cell *, Cell *);
Cell *atom(char *, Cell *);
Cell *object(int, void *);
Cell *list(Cell *, Cell *);
void initial_atom_binding(void);

#endif // BASE_H
