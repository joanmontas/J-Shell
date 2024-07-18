// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#ifndef TEST_HASH_TABLE_H
#define TEST_HASH_TABLE_H
#include <stdio.h>
#include <CUnit/Basic.h>
#include "../../Hash_table/Hash_table.h"

// initializer
void test_hash_table_init();
// interaction
void test_hash_table_insert();
void test_hash_table_search();
void test_hash_table_delete();

#endif // TEST_HASH_TABLE_H
