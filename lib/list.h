#include <stdio.h>
#include <stdlib.h>

#ifndef TRUE
#define TRUE 1
#endif //TRUE
#ifndef FALSE
#define FALSE 0
#endif //TRUE

#ifndef LIST_H
#define LIST_H

typedef struct list {
	void *data;
	struct list *next;
} List;

List *new_list(void *);
int list_append(List *, void *);
int list_insert(List *, void *, int);
/*
 * 1オリジンでアクセスできる。
 * マイナスのインデックスを指定することで後ろから数えてn番目の要素にアクセスできる。
*/
void *list_get(List *, int);
int list_index_of(List *, void *);
void *list_pop(List *, int);
int list_length(List *);
int list_free(List *);

#endif // LIST_H
