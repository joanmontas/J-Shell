// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../List/List.h"
#define HASH_TABLE_CELL_CAPACITY 10

typedef void (*destruct_func)(void *);

typedef struct Hash_table_item {
	char *key;
	void *data;
	destruct_func _destructor;
} Hash_table_item;

typedef struct Hash_table {
	List data[HASH_TABLE_CELL_CAPACITY];
	size_t total_number_of_items;
	size_t number_per_cell[HASH_TABLE_CELL_CAPACITY];

} Hash_table;

// // consturctor and destructor
Hash_table Hash_table_init();
void hash_table_destroy(Hash_table *tbl);
void hash_table_item_destroy(void *itm);
// interaction
int hash_table_insert(Hash_table *tbl, char *key, void *data);
void *hash_table_search(Hash_table *tbl, char *key);
int hash_table_delete(Hash_table *tbl, char *key);
// helper
int hash_table_hash_key(char *key);
#endif // HASH_TABLE_H
