// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#ifndef TEST_LIST_H
#define TEST_LIST_H
#include <stdio.h>
#include <CUnit/Basic.h>
#include "../../List/List.h"

// initializer
void test_list_init();
// append
void test_list_append();
void test_list_append_smart_pointer();
// delete
void test_list_delete_nth();
void test_list_delete_nth_smart_pointer();
void test_list_delete_nth_empty_list();
void test_list_delete_nth_single_node_list();
void test_list_delete_nth_double_node_list();
void test_list_delete_nth_triple_node_list();
// get
void test_list_get_nth_empty_list();
void test_list_get_nth_single_list();
void test_list_get_nth_double_list();
void test_list_get_nth_triple_list();
void test_list_linear_search_exist();
// testing
int helper_numerical_equality(void *l, void *r);
void helper_list_append_and_delete_smart_pointer_destructor(void *data);

#endif