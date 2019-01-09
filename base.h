#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BASE_H
#define BASE_H
#define CELL_LIST_SIZE 4096
#define ATOM_LIST_SIZE 2048
#define OBJECT_LIST_SIZE 2048

enum {CONS, ATOM};
enum {OBJ_NUMBER, OBJ_STRING, OBJ_ATOM, OBJ_CONS, OBJ_NIL, OBJ_T};

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

void init(void);
Cell *cons(Cell *, Cell *);
Cell *list(Cell *, Cell *);
Cell *atom(char *, Cell *);
Cell *nil(void);
Cell *t(void);
Cell *object(int, void *);
double number(Object *);
Object *find_object(void *);
Cell *find_bound_atom(char *);
void dump_cell_list(void);
void dump_bound_atom_list(void);
void dump_object_list(void);
void dump_tree(Cell *);
void visit(Cell *, int);

// gc実装用に確保
// TODO: gcを実装
extern Cell **cell_list;
extern Object **object_list;
// bound_atom識別用に確保
extern Cell **bound_atom_list;

extern int cell_list_next_index;
extern int object_list_next_index;
extern int bound_atom_list_next_index;

#endif // BASE_H
