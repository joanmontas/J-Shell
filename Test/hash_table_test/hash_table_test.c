// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#include "hash_table_test.h"
#include <CUnit/CUnit.h>
#include <string.h>

void test_hash_table_init()
{
	size_t i = 0u;
	Hash_table t = Hash_table_init();
	CU_ASSERT(t.total_number_of_items == 0u);
	for (i = 0; i < HASH_TABLE_CELL_CAPACITY; i++) {
		CU_ASSERT(t.number_per_cell[i] == 0u);
	}
}

void test_hash_table_insert()
{
	char *key0 = "this is just a test";
	int data0 = 123;
	Hash_table t0 = Hash_table_init();
	hash_table_insert(&t0, key0, (void *)(&data0));
	CU_ASSERT(t0.total_number_of_items == 1u);
	hash_table_insert(&t0, "fe4456", (void *)(&data0));
	hash_table_insert(&t0, "8dn3y", (void *)(&data0));
	hash_table_insert(&t0, "lsmd73i", (void *)(&data0));
	CU_ASSERT(t0.total_number_of_items == 4u);
	hash_table_destroy(&t0);

	// empty string
	char *key1 = "";
	char data1[] = "empty-data";
	Hash_table t1 = Hash_table_init();
	hash_table_insert(&t1, key1, (void *)(data1));
	CU_ASSERT(t1.total_number_of_items == 1u);
	hash_table_destroy(&t1);
}

void test_hash_table_search()
{
	char *key0 = "Try t0 f1nd m3!";
	char *key0_to_srch = "Try t0 f1nd m3!";
	char *key0_to_srch_flse = "Try to find me!";

	int *data0 = (int *)malloc(sizeof(int));
	CU_ASSERT(data0 != NULL);
	if (data0 == NULL) {
		return;
	}
	int data0_vle = 123;
	*data0 = data0_vle;

	Hash_table t0 = Hash_table_init();
	hash_table_insert(&t0, key0, (void *)(data0));
	CU_ASSERT(t0.total_number_of_items == 1u);

	int *data0_src_rslt = hash_table_search(&t0, key0_to_srch);
	CU_ASSERT(data0_src_rslt != NULL);
	CU_ASSERT(*((int *)data0_src_rslt) == data0_vle);

	data0_src_rslt = hash_table_search(&t0, key0_to_srch_flse);
	CU_ASSERT(data0_src_rslt == NULL)

	free(data0);
	hash_table_destroy(&t0);

	// empty string
	char *key1 = "";
	char data1[] = "empty-data";
	Hash_table t1 = Hash_table_init();
	hash_table_insert(&t1, key1, (void *)(data1));
	CU_ASSERT(t1.total_number_of_items == 1u);

	int *data1_src_rslt = hash_table_search(&t1, key1);
	CU_ASSERT(data1_src_rslt != NULL);
	CU_ASSERT((strcmp((char *)data1_src_rslt, data1)) == 0);

	data1_src_rslt = hash_table_search(&t1, "non-empty");
	CU_ASSERT(data1_src_rslt == NULL);

	hash_table_destroy(&t1);
}

void test_hash_table_delete()
{
	// deleting non-existing
	Hash_table t0 = Hash_table_init();
	CU_ASSERT(t0.total_number_of_items == 0u);
	int rslt0 = hash_table_delete(&t0, "I dont exist");
	CU_ASSERT(rslt0 == 1);
	hash_table_destroy(&t0);

	// deleting multiple
	char data1[] = "4osm5";
	Hash_table t1 = Hash_table_init();
	CU_ASSERT(t1.total_number_of_items == 0u);
	hash_table_insert(&t1, "", (void *)(data1));
	CU_ASSERT(t1.total_number_of_items == 1u);

	hash_table_insert(&t1, "a", (void *)(data1));
	CU_ASSERT(t1.total_number_of_items == 2u);

	hash_table_insert(&t1, "b", (void *)(data1));
	CU_ASSERT(t1.total_number_of_items == 3u);

	hash_table_insert(&t1, "c", (void *)(data1));
	CU_ASSERT(t1.total_number_of_items == 4u);

	int rslt1 = hash_table_delete(&t1, "b");
	CU_ASSERT(rslt1 == 0);
	CU_ASSERT(t1.total_number_of_items == 3u);

	rslt1 = hash_table_delete(&t1, "");
	CU_ASSERT(rslt1 == 0);
	CU_ASSERT(t1.total_number_of_items == 2u);

	rslt1 = hash_table_delete(&t1, "c");
	CU_ASSERT(rslt1 == 0);
	CU_ASSERT(t1.total_number_of_items == 1u);

	rslt1 = hash_table_delete(&t1, "a");
	CU_ASSERT(rslt1 == 0);
	CU_ASSERT(t1.total_number_of_items == 0u);

	rslt1 = hash_table_delete(&t1, "z");
	CU_ASSERT(rslt1 == 1);
	CU_ASSERT(t1.total_number_of_items == 0u);

	hash_table_destroy(&t1);
}
