#include <stdio.h>
#include "subr.h"

#define STACK_SIZE	2048

Cell *subr_atom(Cell *pointer) {
	return;
}

Cell *subr_car(Cell *pointer) {
	return;
}

Cell *subr_cdr(Cell *pointer) {
	return;
}

Cell *subr_cons(Cell *pointer) {
	return;
}

Cell *subr_eq(Cell *pointer) {
	return;
}

Cell *subr_eval(Cell *pointer) {
	Cell *stack[STACK_SIZE];
	tree(pointer);

	if (strcmp((const char *)pointer->head, "ATOM")) {
		/* code */
	}
	return;
}

Cell *subr_numberp(Cell *pointer) {
	return;
}

Cell *(*subr_funcp_array[])(Cell *) = {
	subr_atom,
	subr_car,
	subr_cdr,
	subr_cons,
	subr_eq,
	subr_eval,
	subr_numberp
};

char *subr_binded_atom_array[] = {
	"atom",
	"car",
	"cdr",
	"cons",
	"eq",
	"eval",
	"numberp"
}