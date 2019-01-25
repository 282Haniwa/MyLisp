#include "list.h"

static List *EMPTY_LIST_DATA = NULL;

List *list_empty_data(void) {
    List *list;

    if (EMPTY_LIST_DATA != NULL) {
        return EMPTY_LIST_DATA;
    }
    EMPTY_LIST_DATA = malloc(sizeof(List *));
    EMPTY_LIST_DATA->data = NULL;
    EMPTY_LIST_DATA->next = NULL;
    return EMPTY_LIST_DATA;
}

List *list_empty(void) {
    List *list;

    list = malloc(sizeof(List *));
    list->data = list_empty_data();
    list->next = NULL;
    return list;
}

int list_is_empty(List *list) {
    if (list->data == list_empty_data()) {
        return (TRUE);
    }
    return (FALSE);
}

List *new_list(void *new_element) {
    List *pointer;

    if (new_element == NULL) {
        return (list_empty());
    }

    pointer = (List *)malloc(sizeof(List *));
    pointer->data = new_element;
    pointer->next = NULL;
    return (pointer);
}

int list_append(List *list, void *new_element) {
    List *pointer;

    if (list_is_empty(list)) {
        list->data = new_element;
        list->next = NULL;
        return (TRUE);
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

    if (list_is_empty(list)) {
        return (FALSE);
    }
    length = list_length(list);
    if (index == 0 || index > length || index < -length) {
        return (FALSE);
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
            void *data;
            List *next, *new;

            data = pointer->data;
            next = pointer->next;
            pointer->data = new_element;
            new = malloc(sizeof(List *));
            new->data = data;
            new->next = next;
            pointer->next = new;
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

    if (list_is_empty(list)) {
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
    while (pointer != NULL) {
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

    if (list_is_empty(list) || target == NULL) {
        return (0);
    }

    counter = 0;
    pointer = list;
    while (pointer != NULL) {
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

    if (list_is_empty(list)) {
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
            return (target);
        }
        pointer = pointer->next;
    }
    return (target);
}

int list_length(List *list) {
    int counter = 0;
    List *pointer;

    if (list_is_empty(list)) {
        return (0);
    }

    pointer = list;
    while (pointer != NULL) {
        pointer = pointer->next;
        counter++;
    }
    return (counter);
}

int list_free(List *list) {
    List *pointer, *next;

    if (list_is_empty(list)) {
        return (TRUE);
    }

    pointer = list;
    while (pointer != NULL) {
        next = pointer->next;
        free(pointer);
        pointer = next;
    }
    return (TRUE);
}
