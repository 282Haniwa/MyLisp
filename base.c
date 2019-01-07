#include "base.h"

Cell *cons(Cell *car, Cell *cdr) {
	Cell *pointer;

	pointer = (Cell *)malloc(sizeof(Cell));
	pointer->kind = CONS;
	pointer->head = car;
	pointer->tail = cdr;
	return(pointer);
}

Cell *atom(char *atomic_symbol, Cell *object_pointer) {
	Cell *pointer;

	pointer = (Cell *)malloc(sizeof(Cell));
	pointer->kind = ATOM;
	pointer->head = (Cell *)strdup(atomic_symbol);
	pointer->tail = (Cell *)object_pointer;
	return(pointer);
}

Cell *object(int object_type, void *value) {
	Object *object_pointer;
	Cell *pointer;

	object_pointer = (Object *)malloc(sizeof(Object));
	pointer = (Cell *)malloc(sizeof(Cell));

	if (object_type == OBJ_INTEGER) {
		long *value_pointer = (long *)malloc(sizeof(long));
		*value_pointer = strtol((char *)value, NULL, 10);
		object_pointer->kind = OBJ_INTEGER;
		object_pointer->value = (void *)value_pointer;
		pointer->head = (Cell *)strdup("INTEGER");
	}

	if (object_type == OBJ_REAL) {
		double *value_pointer = (double *)malloc(sizeof(double));
		*value_pointer = strtod((char *)value, NULL);
		object_pointer->kind = OBJ_REAL;
		object_pointer->value = (void *)value_pointer;
		pointer->head = (Cell *)strdup("REAL");
	}

	if (object_type == OBJ_STRING) {
		char *value_pointer = (char *)malloc(sizeof(char));
		value_pointer = (char *)value;
		object_pointer->kind = OBJ_STRING;
		object_pointer->value = (void *)value_pointer;
		pointer->head = (Cell *)strdup("STRING");
	}

	if (object_type == OBJ_ATOM) {
		object_pointer->kind = OBJ_ATOM;
		object_pointer->value = (void *)value;
		pointer->head = (Cell *)strdup("ATOM");
	}

	if (object_type == OBJ_LIST) {
		object_pointer->kind = OBJ_LIST;
		object_pointer->value = (void *)value;
		pointer->head = (Cell *)strdup("LIST");
	}

	object_pointer->bound = 1;
	pointer->kind = OBJECT;
	pointer->tail = (Cell *)object_pointer;
	return(pointer);
}

Cell *list(Cell *previous_list, Cell *new_element) {
	Cell *pointer;

	pointer = previous_list;
	while(strcmp((const char *)pointer->tail->head, "nil")){
		pointer = pointer->tail;
	}
	pointer->tail = new_element;
	return(previous_list);
}

void initial_atom_binding(void) {

}
