// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#include "list_test.h"
#include <CUnit/CUnit.h>
#include <CUnit/TestRun.h>

void test_list_init()
{
	List l = List_init();
	CU_ASSERT(l.size == 0u);
	CU_ASSERT(l.data == NULL);
	list_destroy(&l);
}

void test_list_append()
{
	List l0 = List_init();
	int rslt0 = 0;

	int data0 = 123;
	int data1 = 56756;
	int data2 = -9463;

	rslt0 = list_append(&l0, &data0);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l0.size == 1u);
	CU_ASSERT(*((int *)l0.data->data) == data0);

	rslt0 = list_append(&l0, &data1);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l0.size == 2u);
	CU_ASSERT(*((int *)l0.data->next->data) == data1);

	rslt0 = list_append(&l0, &data2);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l0.size == 3u);
	CU_ASSERT(*((int *)l0.data->next->next->data) == data2);

	list_destroy(&l0);
}

void test_list_append_smart_pointer()
{
	List l0 = List_init();
	int rslt0 = 0;

	int *some_data = malloc(sizeof(int));
	CU_ASSERT(some_data != NULL);

	*some_data = 122333;

	CU_ASSERT(*some_data == 122333);

	rslt0 = list_append_smart_pointer(
		&l0, some_data,
		helper_list_append_and_delete_smart_pointer_destructor);
	CU_ASSERT(rslt0 == 0);

	list_destroy(&l0);
}

void test_list_delete_nth()
{
	List l0 = List_init();
	int data0 = 345;
	int rslt0 = 0;

	rslt0 = list_delete_nth(&l0, 0);
	CU_ASSERT(rslt0 == -1);

	rslt0 = list_append(&l0, &data0);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l0.size == 1u);
	CU_ASSERT(*((int *)l0.data->data) == data0);

	rslt0 = list_delete_nth(&l0, 0);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l0.size == 0u);
	CU_ASSERT(l0.data == NULL);

	list_destroy(&l0);
}

void test_list_delete_nth_smart_pointer()
{
	List l0 = List_init();
	int rslt0 = 0;

	int *some_data = malloc(sizeof(int));
	CU_ASSERT(some_data != NULL);

	*some_data = 555554444;

	CU_ASSERT(*some_data == 555554444);

	rslt0 = list_append_smart_pointer(
		&l0, some_data,
		helper_list_append_and_delete_smart_pointer_destructor);

	CU_ASSERT(rslt0 == 0);

	list_destroy(&l0);
}

void test_list_delete_nth_empty_list()
{
	List l0 = List_init();
	int rslt0 = 0;
	int data0 = 56456;

	rslt0 = list_append(&l0, &data0);
	CU_ASSERT(rslt0 == 0);
	rslt0 = list_delete_nth(&l0, 0);
	CU_ASSERT(rslt0 == -1);

	list_destroy(&l0);
}

void test_list_delete_nth_single_node_list()
{
	List l0 = List_init();
	int data0 = 123;
	int rslt0 = 0;

	rslt0 = list_append(&l0, &data0);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l0.size == 1u);
	rslt0 = list_delete_nth(&l0, 0);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l0.size == 0u);

	list_destroy(&l0);
}

void test_list_delete_nth_double_node_list()
{
	// delete first
	List l0 = List_init();
	int data0 = 937567;
	int data1 = 4564;
	int rslt0 = 0;

	rslt0 = list_append(&l0, &data0);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l0.size == 1u);

	rslt0 = list_append(&l0, &data1);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l0.size == 2u);

	rslt0 = list_delete_nth(&l0, 0);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l0.size == 1u);

	CU_ASSERT(*((int *)l0.data->data) == data1);

	list_destroy(&l0);

	// delete second
	List l1 = List_init();

	rslt0 = list_append(&l1, &data0);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l1.size == 1u);

	rslt0 = list_append(&l1, &data1);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l1.size == 2u);

	rslt0 = list_delete_nth(&l1, 1u);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l1.size == 1u);

	CU_ASSERT(*((int *)l1.data->data) == data0);

	list_destroy(&l1);
}

void test_list_delete_nth_triple_node_list()
{
	int data0 = 805746;
	int data1 = 94729;
	int data2 = 8246;
	int rslt0 = 0;

	// delete first
	List l0 = List_init();

	rslt0 = list_append(&l0, &data0);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l0.size == 1u);

	rslt0 = list_append(&l0, &data1);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l0.size == 2u);

	rslt0 = list_append(&l0, &data2);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l0.size == 3u);

	rslt0 = list_delete_nth(&l0, 0);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l0.size == 2u);

	CU_ASSERT(*((int *)l0.data->data) == data1);
	CU_ASSERT(*((int *)l0.data->next->data) == data2);

	list_destroy(&l0);

	// delete second
	List l1 = List_init();

	rslt0 = list_append(&l1, &data0);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l1.size == 1u);

	rslt0 = list_append(&l1, &data1);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l1.size == 2u);

	rslt0 = list_append(&l1, &data2);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l1.size == 3u);

	rslt0 = list_delete_nth(&l1, 1u);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l1.size == 2u);

	CU_ASSERT(*((int *)l1.data->data) == data0);
	CU_ASSERT(*((int *)l1.data->next->data) == data2);

	list_destroy(&l1);

	// delete second
	List l2 = List_init();

	rslt0 = list_append(&l2, &data0);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l2.size == 1u);

	rslt0 = list_append(&l2, &data1);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l2.size == 2u);

	rslt0 = list_append(&l2, &data2);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l2.size == 3u);

	rslt0 = list_delete_nth(&l2, 2u);
	CU_ASSERT(rslt0 == 0);
	CU_ASSERT(l2.size == 2u);

	CU_ASSERT(*((int *)l2.data->data) == data0);
	CU_ASSERT(*((int *)l2.data->next->data) == data1);

	list_destroy(&l2);
}

void test_list_get_nth_empty_list()
{
	List l0 = List_init();
	void *rslt0 = NULL;

	rslt0 = list_get_nth(&l0, 0);
	CU_ASSERT(rslt0 == NULL);

	list_destroy(&l0);
}

void test_list_get_nth_single_list()
{
	List l0 = List_init();
	int data0 = 34545;
	void *rslt0 = NULL;
	int flag = 0;

	flag = list_append(&l0, &data0);
	CU_ASSERT(flag == 0);

	rslt0 = list_get_nth(&l0, 1u);
	CU_ASSERT(rslt0 == NULL);

	rslt0 = list_get_nth(&l0, 0u);
	CU_ASSERT(rslt0 != NULL);

	list_destroy(&l0);
}

void test_list_get_nth_double_list()
{
	List l0 = List_init();
	int data0 = 297;
	int data1 = 25842;
	void *rslt0 = NULL;
	int flag = 0;

	flag = list_append(&l0, &data0);
	CU_ASSERT(flag == 0);

	flag = list_append(&l0, &data1);
	CU_ASSERT(flag == 0);

	rslt0 = list_get_nth(&l0, 0u);
	CU_ASSERT((*(int *)rslt0) == data0);

	rslt0 = list_get_nth(&l0, 1u);
	CU_ASSERT((*(int *)rslt0) == data1);

	rslt0 = list_get_nth(&l0, 2u);
	CU_ASSERT(rslt0 == NULL);

	list_destroy(&l0);
}

void test_list_get_nth_triple_list()
{
	int data0 = 736654;
	int data1 = 3653;
	int data2 = 92753;
	void *rslt0 = NULL;
	int flag = 0;

	List l0 = List_init();
	flag = list_append(&l0, &data0);
	CU_ASSERT(flag == 0);

	flag = list_append(&l0, &data1);
	CU_ASSERT(flag == 0);

	flag = list_append(&l0, &data2);
	CU_ASSERT(flag == 0);

	rslt0 = list_get_nth(&l0, 0u);
	CU_ASSERT((*(int *)rslt0) == data0);

	rslt0 = list_get_nth(&l0, 1u);
	CU_ASSERT((*(int *)rslt0) == data1);

	rslt0 = list_get_nth(&l0, 2u);
	CU_ASSERT((*(int *)rslt0) == data2);

	rslt0 = list_get_nth(&l0, 3u);
	CU_ASSERT(rslt0 == NULL);

	list_destroy(&l0);
}

void test_list_linear_search_exist()
{
	int rslt0 = 0;
	List l0 = List_init();

	int *value_x = malloc(sizeof(int));
	int *value_0 = malloc(sizeof(int));
	int *value_1 = malloc(sizeof(int));
	int *value_2 = malloc(sizeof(int));
	int *value_3 = malloc(sizeof(int));
	int *value_4 = malloc(sizeof(int));

	*value_0 = 123;
	*value_1 = 321;
	*value_2 = 5667;
	*value_3 = 67867;
	*value_4 = 546834392;

	// setup the lists = [value_0, value_1, ..., value_4]
	rslt0 = list_append_smart_pointer(
		&l0, value_0,
		helper_list_append_and_delete_smart_pointer_destructor);
	CU_ASSERT(rslt0 == 0);

	rslt0 = list_append_smart_pointer(
		&l0, value_1,
		helper_list_append_and_delete_smart_pointer_destructor);
	CU_ASSERT(rslt0 == 0);

	rslt0 = list_append_smart_pointer(
		&l0, value_2,
		helper_list_append_and_delete_smart_pointer_destructor);
	CU_ASSERT(rslt0 == 0);

	rslt0 = list_append_smart_pointer(
		&l0, value_3,
		helper_list_append_and_delete_smart_pointer_destructor);
	CU_ASSERT(rslt0 == 0);

	rslt0 = list_append_smart_pointer(
		&l0, value_4,
		helper_list_append_and_delete_smart_pointer_destructor);
	CU_ASSERT(rslt0 == 0);

	// search
	*value_x = 9999;
	rslt0 = list_linear_search_exist(&l0, value_x,
					 helper_numerical_equality);
	CU_ASSERT(rslt0 == -1);

	*value_x = *value_0;
	rslt0 = list_linear_search_exist(&l0, value_x,
					 helper_numerical_equality);
	CU_ASSERT(rslt0 == 0);

	*value_x = *value_1;
	rslt0 = list_linear_search_exist(&l0, value_x,
					 helper_numerical_equality);
	CU_ASSERT(rslt0 == 1);

	*value_x = *value_2;
	rslt0 = list_linear_search_exist(&l0, value_x,
					 helper_numerical_equality);
	CU_ASSERT(rslt0 == 2);

	*value_x = *value_3;
	rslt0 = list_linear_search_exist(&l0, value_x,
					 helper_numerical_equality);
	CU_ASSERT(rslt0 == 3);

	*value_x = *value_4;
	rslt0 = list_linear_search_exist(&l0, value_x,
					 helper_numerical_equality);
	CU_ASSERT(rslt0 == 4);

	list_destroy(&l0);
	free(value_x);
}

int helper_numerical_equality(void *l, void *r)
{
	int *l_int = (int *)l;
	int *r_int = (int *)r;

	if (l == NULL || r == NULL) {
		fprintf(stderr,
			"ERROR: helper_numerical_equality error. Given pointers are NULL\n");
		return -1;
	}

	if (*l_int == *r_int) {
		return 1;
	}

	return 0;
}

void helper_list_append_and_delete_smart_pointer_destructor(void *data)
{
	int *some_data = (int *)data;
	free(some_data);
}