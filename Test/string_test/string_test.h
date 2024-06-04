// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#ifndef TEST_STRING_H
#define TEST_STRING_H
#include <stdio.h>
#include <CUnit/Basic.h>
#include "../../String/String.h"

void test_string_init_default();
void test_string_init_c_string();
void test_string_compare();
void test_string_at();
void test_string_pop_back();
void test_string_append_char();

#endif