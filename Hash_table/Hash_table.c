// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#include "Hash_table.h"
#include <string.h>

Hash_table Hash_table_init()
{
	Hash_table ht;
	size_t i;
	for (i = 0; i < HASH_TABLE_CELL_CAPACITY; i++) {
		ht.number_per_cell[i] = 0u;
		ht.data[i] = List_init();
	}
	ht.total_number_of_items = 0u;
	return ht;
}

int hash_table_insert(Hash_table *tbl, char *key, void *data)
{
	int rslt = 0;
	int h = 0;
	Hash_table_item *itm = NULL;

	if (tbl == NULL) {
		fprintf(stderr,
			"ERROR: hash_table_insert error. Given table is NULL\n");
		return -1;
	}

	if (key == NULL) {
		fprintf(stderr,
			"ERROR: hash_table_insert error. Given key is NULL\n");
		return -1;
	}

	h = hash_table_hash_key(key);

	if (h == -1) {
		fprintf(stderr,
			"ERROR: hash_table_insert error. Error while hashing key\n");
		return -1;
	}

	itm = (Hash_table_item *)malloc(sizeof(Hash_table_item));
	if (itm == NULL) {
		fprintf(stderr,
			"ERROR: hash_table_insert error. Could not allocate memory for new item\n");
		return -1;
	}

	// itm->key = key;
	itm->key = (char *)malloc(strlen(key) + 1);
	if (itm->key == NULL) {
		fprintf(stderr,
			"ERROR: hash_table_insert error. Could not allocate memory for new key\n");
		free(itm);
		return -1;
	}
	strcpy(itm->key, key);

	itm->data = data;
	itm->_destructor =
		NULL; // NOTE(Joan) To be used by smart pointer - Joan

	rslt = list_append_smart_pointer(&(tbl->data[h]), (void *)itm,
					 hash_table_item_destroy);
	if (rslt == -1) {
		free(itm->key);
		free(itm);
		fprintf(stderr,
			"ERROR: hash_table_insert error. Error while appending key-data pair\n");
		return -1;
	}

	tbl->total_number_of_items++;
	tbl->number_per_cell[h]++;

	return 0;
}

int hash_table_hash_key(char *key)
{
	int h = 0;
	size_t i = 0u;
	char c = '\0';

	if (key == NULL) {
		fprintf(stderr,
			"ERROR: Hash_table's hash_key error. Given Key is NULL\n");
		return -1;
	}

	while (1) {
		c = key[i];
		if (c == '\0') {
			break;
		}
		h = h + ((int)c);
		i++;
	}

	return h % HASH_TABLE_CELL_CAPACITY;
}

void hash_table_item_destroy(void *itm)
{
	Hash_table_item *ht_itm = (Hash_table_item *)itm;
	free(ht_itm->key);
	ht_itm->key = NULL; // redundant
	free(itm);
	itm = NULL;
}

void hash_table_destroy(Hash_table *tbl)
{
	size_t i = 0u;

	if (tbl == NULL) {
		return;
	}

	for (i = 0; i < HASH_TABLE_CELL_CAPACITY; i++) {
		tbl->number_per_cell[i] = 0u;
		list_destroy(&tbl->data[i]);
	}

	tbl->total_number_of_items = 0u;
	return;
}

void *hash_table_search(Hash_table *tbl, char *key)
{
	int h;
	List current_list;
	Hash_table_item *current_cell = NULL;

	if (tbl == NULL) {
		fprintf(stderr,
			"ERROR: hash_table_seach error. Given table is NULL\n");
		return NULL;
	}

	if (key == NULL) {
		fprintf(stderr,
			"ERROR: hash_table_seach error. Given key is NULL\n");
		return NULL;
	}

	h = hash_table_hash_key(key);

	if (h == -1) {
		fprintf(stderr,
			"ERROR: hash_table_search error. Error while hashing key\n");
		return NULL;
	}

	if (tbl->number_per_cell[h] == 0) {
		return NULL;
	}

	current_list = tbl->data[h];
	for (size_t i = 0u; i < current_list.size; i++) {
		current_cell = list_get_nth(&current_list, i);
		if (current_cell == NULL) {
			fprintf(stderr,
				"ERROR: hash_table_search error. Error while searching key\n");
			return NULL;
		}

		if (strcmp(current_cell->key, key) == 0) {
			return current_cell->data;
		}
	}

	return NULL;
}

int hash_table_delete(Hash_table *tbl, char *key)
{
	int h;
	List current_list;
	Hash_table_item *current_cell = NULL;

	if (tbl == NULL) {
		fprintf(stderr,
			"ERROR: hash_table_delete error. Given table is NULL\n");
		return -1;
	}

	if (key == NULL) {
		fprintf(stderr,
			"ERROR: hash_table_delete error. Given key is NULL\n");
		return -1;
	}

	h = hash_table_hash_key(key);

	if (h == -1) {
		fprintf(stderr,
			"ERROR: hash_table_delete error. Error while hashing key\n");
		return -1;
	}

	current_list = tbl->data[h];
	for (size_t i = 0u; i < current_list.size; i++) {
		current_cell = list_get_nth(&current_list, i);
		if (current_cell == NULL) {
			fprintf(stderr,
				"ERROR: hash_table_delete error. Error while searching key\n");
			return -1;
		}

		if (strcmp(current_cell->key, key) == 0) {
			list_delete_nth(&(tbl->data[h]), i);
			tbl->total_number_of_items--;
			tbl->number_per_cell[h]--;
			return 0;
		}
	}

	return 1;
}