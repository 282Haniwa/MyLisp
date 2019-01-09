#include "base.h"

Cell **cell_list;
Object **object_list;
Cell **bound_atom_list;
int cell_list_next_index = 0;
int object_list_next_index = 0;
int bound_atom_list_next_index = 0;

void init(void) {
	cell_list = (Cell **)malloc(CELL_LIST_SIZE * sizeof(Cell *));
	object_list = (Object **)malloc(OBJECT_LIST_SIZE * sizeof(Object *));
	bound_atom_list = (Cell **)malloc(ATOM_LIST_SIZE * sizeof(Cell *));
	cell_list_next_index = 0;
	object_list_next_index = 0;
	bound_atom_list_next_index = 0;

	bound_atom_list[bound_atom_list_next_index++] = nil();
	bound_atom_list[bound_atom_list_next_index++] = t();
}

Cell *cons(Cell *car, Cell *cdr) {
	Cell *pointer;

	pointer = (Cell *)malloc(sizeof(Cell));
	pointer->kind = CONS;
	pointer->head = car;
	pointer->tail = cdr;
	cell_list[cell_list_next_index++] = pointer;
	return(pointer);
}

Cell *list(Cell *previous_list, Cell *new_element) {
	Cell *pointer;

	pointer = previous_list;
	while(pointer->tail != nil()){
		pointer = pointer->tail;
	}
	pointer->tail = new_element;
	return(previous_list);
}

Cell *atom(char *atomic_symbol, Cell *object_pointer) {
	Cell *pointer;

	if (object_pointer == NULL) {
		pointer = find_bound_atom(atomic_symbol);
		if (pointer != NULL) {
			return(pointer);
		}
	}

	pointer = (Cell *)malloc(sizeof(Cell));
	pointer->kind = ATOM;
	pointer->head = (Cell *)strdup(atomic_symbol);
	pointer->tail = (Cell *)object_pointer;
	cell_list[cell_list_next_index++] = pointer;
	return(pointer);
}

Cell *nil(void) {
	Object *object_pointer;
	Cell *cell_pointer = NULL;

	cell_pointer = find_bound_atom("nil");
	if (cell_pointer != NULL) {
		return(cell_pointer);
	}

	object_pointer = (Object *)malloc(sizeof(Object));
	object_pointer->kind = OBJ_NIL;
	object_pointer->bound = 1;
	object_pointer->value = (void *)strdup("nil");
	cell_pointer = (Cell *)malloc(sizeof(Cell));
	cell_pointer->kind = ATOM;
	cell_pointer->head = (Cell *)strdup("nil");
	cell_pointer->tail = (Cell *)object_pointer;
	object_list[object_list_next_index++] = object_pointer;
	return(cell_pointer);
}

Cell *t(void) {
	Object *object_pointer;
	Cell *cell_pointer = NULL;

	cell_pointer = find_bound_atom("t");
	if (cell_pointer != NULL) {
		return(cell_pointer);
	}

	object_pointer = (Object *)malloc(sizeof(Object));
	object_pointer->kind = OBJ_T;
	object_pointer->bound = 1;
	object_pointer->value = (void *)strdup("t");
	cell_pointer = (Cell *)malloc(sizeof(Cell));
	cell_pointer->kind = ATOM;
	cell_pointer->head = (Cell *)strdup("t");
	cell_pointer->tail = (Cell *)object_pointer;
	object_list[object_list_next_index++] = object_pointer;
	return(cell_pointer);
}

Cell *object(int object_type, void *value) {
	Object *object_pointer = NULL;

	object_pointer = find_object(value);
	if (object_pointer != NULL) {
		return((Cell *)object_pointer);
	}

	object_pointer = (Object *)malloc(sizeof(Object));

	if (object_type == OBJ_NUMBER) {
		object_pointer->kind = OBJ_NUMBER;
		object_pointer->value = (void *)strdup(value);
	}

	if (object_type == OBJ_STRING) {
		object_pointer->kind = OBJ_STRING;
		object_pointer->value = (void *)strdup(value);
	}

	if (object_type == OBJ_ATOM) {
		object_pointer->kind = OBJ_ATOM;
		object_pointer->value = (void *)value;
	}

	if (object_type == OBJ_CONS) {
		object_pointer->kind = OBJ_CONS;
		object_pointer->value = (void *)value;
	}

	object_pointer->bound = 1;
	object_list[object_list_next_index++] = object_pointer;
	return((Cell *)object_pointer);
}

double number(Object *object_pointer) {
	double value = strtod((char *)object_pointer->value, NULL);
	return(value);
}

Object *find_object(void *object_value) {
	int n = 0;
	Object *pointer;

	// 線形探索は効率が悪い
	while(n < object_list_next_index){
		pointer = object_list[n++];
		if (pointer->kind == OBJ_ATOM || pointer->kind == OBJ_CONS) {
			if (object_value == pointer->value) {
				return(pointer);
			}
		} else {
			if (!strcmp((const char *)object_value, (const char *)pointer->value)) {
				return(pointer);
			}
		}
	}
	return(NULL);
}

Cell *find_bound_atom(char *atomic_symbol) {
	int n = 0;
	Cell *pointer;

	// 線形探索は効率が悪い
	while(n < bound_atom_list_next_index){
		pointer = bound_atom_list[n++];
		if (!strcmp((const char *)atomic_symbol, (const char *)pointer->head)) {
			return(pointer);
		}
	}
	return(NULL);
}

void dump_cell_list(void) {
	printf("cell count is : %d\n", cell_list_next_index);
	printf("cell list is  :\n");
	for(int i = 0; i < cell_list_next_index; i++){
		dump_tree(cell_list[i]);
		printf("\n");
	}
	printf("--------------------------------\n");
}

void dump_bound_atom_list(void) {
	printf("bound atom count is : %d\n", bound_atom_list_next_index);
	printf("bound atom list is  :\n");
	for(int i = 0; i < bound_atom_list_next_index; i++){
		printf("%s\n", (const char *)bound_atom_list[i]->head);
	}
	printf("--------------------------------\n");
}

void dump_object_list(void) {
	printf("object count is : %d\n", object_list_next_index);
	printf("object list is  :\n");
	for(int i = 0; i < object_list_next_index; i++){
		Object *object_pointer = object_list[i];
		if (object_pointer->kind == OBJ_ATOM) {
			printf("atom(%s)\n", (const char *)((Cell *)object_pointer)->head);
		} else if (object_pointer->kind == OBJ_CONS) {
			dump_tree((Cell *)object_pointer->value);
		} else {
			printf("object(%s)\n", (const char *)object_pointer->value);
		}
	}
	printf("--------------------------------\n");
}

void dump_tree(Cell *pointer) {
	visit(pointer, 1);
	printf("\n");
	printf("--------------------------------\n");
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
	return;
}
