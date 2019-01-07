#include "defs.h"
#include "subr.h"
#include "fsubr.h"

int main(void) {
	linecounter = 1;
	if (yyparse() == 0) {
		fprintf(stderr, "\nparser successfully ended\n\n");
	}
	return(EXIT_SUCCESS);
}

void tree(Cell *pointer) {
	visit(pointer, 1);
	printf("\n");
}

void visit(Cell *pointer, int level) {
	int count;

	printf("\n");
	for (count = 0; count < level; count++) {
		printf("    ");
	}
	if (pointer->kind == CONS) {
		printf("cons(");
		visit(pointer->head, level + 1);
		visit(pointer->tail, level + 1);
		printf(")");
	}
	if (pointer->kind == ATOM) {
		printf("atom(");
		printf("%s", (char *)pointer->head);
		// printf(" %s", (char *)pointer->tail);
		printf(")");
	}
	if (pointer->kind == OBJECT) {
		printf("object(");
		printf("%s ", (char *)pointer->head);
		printf("%s", (char *)((Object *)pointer->tail)->value);
		printf(")");
	}
	return;
}

void evaluate(Cell *pointer) {
	tree(pointer);
	return;
}
