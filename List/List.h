// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef void (*destruct_func)(void *);
typedef int (*equality_func)(void *, void *);

typedef struct List_node {
	void *data;
	struct List_node *next;
	destruct_func _destructor;
} List_node;

typedef struct List {
	size_t size;
	List_node *data;
} List;

// // constructor and destructor
List List_init();
int list_destroy(List *l);
// interaction
int list_append(List *l, void *data);
int list_append_smart_pointer(List *l, void *data, destruct_func func);

int list_delete_nth(List *l, size_t ith);

void *list_get_nth(List *l, size_t ith);

int list_linear_search_exist(List *l, void *data, equality_func func);
// helper
#endif // LIST_H