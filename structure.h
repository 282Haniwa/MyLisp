#ifndef STRUCTURE_H
#define STRUCTURE_H
enum {CONS, NODE, LEAF};

typedef struct cell {
	int          kind;
	struct cell *head;
	struct cell *tail;
} Cell;
#endif // STRUCTURE_H
