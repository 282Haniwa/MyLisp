#include <stdio.h>
#include "fsubr.h"

Cell *fsubr_add(Cell *pinter) {
	return;
}
Cell *fsubr_sub(Cell *pinter) {
	return;
}

Cell *fsubr_mul(Cell *pinter) {
	return;
}

Cell *fsubr_div(Cell *pinter) {
	return;
}

Cell *fsubr_mod(Cell *pinter) {
	return;
}

Cell *fsubr_cond(Cell *pinter) {
	return;
}

Cell *fsubr_define(Cell *pinter) {
	return;
}

Cell *fsubr_lambda(Cell *pinter) {
	return;
}

Cell *fsubr_quote(Cell *pinter) {
	return;
}

Cell *(*subr_funcp_array[])(Cell *) = {
	fsubr_add,
	fsubr_sub,
	fsubr_mul,
	fsubr_div,
	fsubr_mod,
	fsubr_cond,
	fsubr_define,
	fsubr_lambda,
	fsubr_quote
};

char *subr_binding_atom_array[] = {
	"+",
	"-",
	"*",
	"/",
	"%",
	"cond",
	"define",
	"lambda",
	"quote"
}
