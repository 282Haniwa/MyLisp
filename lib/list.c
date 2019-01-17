#include "list.h"

List *new_list(void *new_element) {
    List *pointer;

    pointer = (List *)malloc(sizeof(List *));
    pointer->data = new_element;
    pointer->next = NULL;
    return (pointer);
}

int list_append(List *list, void *new_element) {
    List *pointer;

    if (list == NULL) {
        return (FALSE);
    }
    pointer = list;
    while (pointer->next != NULL) {
        pointer = pointer->next;
    }
    pointer->next = new_list(new_element);
    return (TRUE);
}

void *list_pop(List *list, void *target) {
    List *pointer;
    void *result;

    if (list == NULL) {
        return (NULL);
    }
    pointer = list;
    while (pointer->next != NULL) {
        if (pointer->data == target) {
            List *tmp = pointer->next;
            result = pointer->data;
            free(pointer);
            pointer = tmp;
            return (result);
        }
        pointer = pointer->next;
    }
    if (target == NULL) {
        result = pointer->data;
        free(pointer);
        pointer = NULL;
        return (result);
    }
    return (NULL);
}

int list_length(List *list) {
    int counter = 0;
    List *pointer;

    pointer = list;
    while (pointer->next != NULL) {
        pointer = pointer->next;
        counter++;
    }
    return (counter);
}

int list_free(List *list) {
    List *pointer, *next;

    pointer = list;
    while (pointer != NULL) {
        next = pointer->next;
        free(pointer);
        pointer = next;
    }
    return (TRUE);
}
