// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#include "List.h"

List List_init()
{
	List l;
	l.size = 0u;
	l.data = NULL;
	return l;
}

int list_append(List *l, void *data)
{
	List_node *ln = NULL;
	List_node *cur_n = NULL;

	if (l == NULL) {
		fprintf(stderr,
			"ERROR: list_insert error. Given list is NULL\n");
		return -1;
	}

	ln = (List_node *)malloc(sizeof(List_node));

	if (ln == NULL) {
		fprintf(stderr,
			"ERROR: List_insert error. Could not allocate memory for new list node\n");
		return -1;
	}

	ln->next = NULL;
	ln->data = data;
	ln->_destructor = NULL;

	if (l->data == NULL) {
		l->data = ln;
		l->size = 1u;
		return 0;
	} else {
		cur_n = l->data;
		while (cur_n != NULL) {
			if (cur_n->next == NULL) {
				cur_n->next = ln;
				l->size = l->size + 1;
				return 0;
			}
			cur_n = cur_n->next;
		}
	}

	return 1;
}

int list_append_smart_pointer(List *l, void *data, destruct_func func)
{
	List_node *ln = NULL;
	List_node *cur_n = NULL;

	if (l == NULL) {
		fprintf(stderr,
			"ERROR: list_insert error. Given list is NULL\n");
		return -1;
	}

	ln = (List_node *)malloc(sizeof(List_node));

	if (ln == NULL) {
		fprintf(stderr,
			"ERROR: List_insert error. Could not allocate memory for new list node\n");
		return -1;
	}

	ln->next = NULL;
	ln->data = data;
	ln->_destructor = func;

	if (l->data == NULL) {
		l->data = ln;
		l->size = 1u;
		return 0;
	} else {
		cur_n = l->data;
		while (cur_n != NULL) {
			if (cur_n->next == NULL) {
				cur_n->next = ln;
				l->size = l->size + 1;
				return 0;
			}
			cur_n = cur_n->next;
		}
	}

	return 1;
}

int list_delete_nth(List *l, size_t ith)
{
	size_t i = 1u;
	List_node *cur_ln = NULL;
	List_node *temp_ln = NULL;
	if (l == NULL) {
		fprintf(stderr,
			"ERROR: list_delete_nth error. Given list is NULL\n");
		return -1;
	}

	if (ith > l->size) {
		fprintf(stderr,
			"ERROR: list_delete_nth error. ith is out of range\n");
		return -1;
	}

	if (l->data == NULL) {
		fprintf(stderr,
			"ERROR: list_delete_nth error. List's data in NULL\n");
		return -1;
	}

	cur_ln = l->data;

	if (ith == 0u) {
		cur_ln = cur_ln->next;

		if (l->data->_destructor != NULL) {
			l->data->_destructor(l->data->data);
		}

		free(l->data);

		l->data = cur_ln;
		l->size--;
		return 0;
	}

	while (cur_ln != NULL) {
		if (i == ith) {
			temp_ln = cur_ln->next;
			cur_ln->next = cur_ln->next->next;

			// smart pointer
			if (temp_ln->_destructor != NULL) {
				temp_ln->_destructor(temp_ln->data);
			}
			free(temp_ln);

			l->size--;
			return 0;
		}
		cur_ln = cur_ln->next;
		i++;
	}
	return 1;
}

void *list_get_nth(List *l, size_t ith)
{
	size_t i = 0u;
	List_node *cur_ln = NULL;
	if (l == NULL) {
		fprintf(stderr,
			"ERROR: list_get_nth error. Given list is NULL\n");
		return NULL;
	}

	if (ith > l->size) {
		fprintf(stderr,
			"ERROR: list_get_nth error. ith is out of range\n");
		return NULL;
	}

	if (l->data == NULL) {
		fprintf(stderr,
			"ERROR: list_get_nth error. List's data in NULL\n");
		return NULL;
	}

	cur_ln = l->data;

	while (cur_ln != NULL) {
		if (i == ith) {
			return cur_ln->data;
		}
		cur_ln = cur_ln->next;
		i++;
	}
	return NULL;
}

int list_linear_search_exist(List *l, void *data, equality_func func)
{
	int ith = 0;
	List_node *cur_ln = NULL;

	if (l == NULL) {
		fprintf(stderr,
			"ERROR: list_linear_search_exist error. Given list is NULL\n");
		return -1;
	}

	if (func == NULL) {
		fprintf(stderr,
			"ERROR: list_linear_search_exist error. Given function is NULL\n");
		return -1;
	}

	if (l->data == NULL) {
		fprintf(stderr,
			"ERROR: list_linear_search_exist error. List's data in NULL\n");
		return -1;
	}

	cur_ln = l->data;
	while (cur_ln != NULL) {
		if (func(data, cur_ln->data) == 1) {
			return ith;
		}
		ith = ith + 1;
		cur_ln = cur_ln->next;
	}
	return -1;
}

int list_destroy(List *l)
{
	List_node *cur_n = NULL;
	List_node *temp_n = NULL;

	if (l == NULL) {
		fprintf(stderr,
			"ERROR: list_destroy error. Given list is NULL\n");
		return -1;
	}

	cur_n = l->data;
	while (1) {
		if (cur_n == NULL) {
			return 0;
		}

		temp_n = cur_n;
		cur_n = cur_n->next;

		// smart pointer
		if (temp_n->_destructor != NULL) {
			temp_n->_destructor(temp_n->data);
		}

		free(temp_n);
	}
	return 1;
}
