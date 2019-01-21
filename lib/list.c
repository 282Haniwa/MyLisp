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

int list_insert(List *list, void *new_element, int index) {
    int counter, length, target_index;
    List *pointer;
    void *target = NULL;

    if (list == NULL) {
        return (NULL);
    }
    length = list_length(list);
    if (index == 0 || index > length || index < -length) {
        return (NULL);
    }

    if (index < 0) {
        target_index = length + index + 1;
    } else {
        target_index = index;
    }

    counter = 0;
    pointer = list;
    while (pointer != NULL) {
        counter++;
        if (counter == target_index) {
            List *tmp = pointer->next;
            pointer->data = new_element;
            pointer->next = tmp;
            return (TRUE);
        }
        pointer = pointer->next;
    }
    return (FALSE);
}

void *list_get(List *list, int index) {
    int counter, length, target_index;
    List *pointer;
    void *target = NULL;

    if (list == NULL) {
        return (NULL);
    }
    length = list_length(list);
    if (index > length || index < -length) {
        return (NULL);
    }

    if (index < 0) {
        target_index = length + index + 1;
    } else {
        target_index = index;
    }

    counter = 0;
    pointer = list;
    while (pointer->next != NULL) {
        counter++;
        if (target_index == counter) {
            target = pointer->data;
        }
        pointer = pointer->next;
    }
    return (target);
}

int list_index_of(List *list, void *target) {
    int counter, target_index;
    List *pointer;

    if (list == NULL || target == NULL) {
        return (0);
    }

    pointer = list;
    while (pointer->next != NULL) {
        counter++;
        if (pointer->data == target) {
            return (counter);
        }
        pointer = pointer->next;
    }
    return (0);
}

void *list_pop(List *list, int index) {
    int counter, length, target_index;
    List *pointer;
    void *target = NULL;

    if (list == NULL) {
        return (NULL);
    }
    length = list_length(list);
    if (index == 0 || index > length || index < -length) {
        return (NULL);
    }

    if (index < 0) {
        target_index = length + index + 1;
    } else {
        target_index = index;
    }

    counter = 0;
    pointer = list;
    while (pointer->next != NULL) {
        counter++;
        if (counter == target_index - 1) {
            List *tmp = pointer->next->next;
            target = pointer->next->data;
            free(pointer->next);
            pointer->next = tmp;
        }
        pointer = pointer->next;
    }
    return (target);
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
