// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#include "string_test.h"

#define DEFAULT_CAPACITY 7u

void test_string_init_default()
{
	String *str = string_init_default();

	CU_ASSERT(str->size == 0u);
	CU_ASSERT(str->capacity == DEFAULT_CAPACITY);
	CU_ASSERT(sizeof(str->c_string) == (str->capacity * sizeof(char) + 1u));

	// I should be able to use standard function without any error
	printf("test_string_init_default print: %s\n", str->c_string);

	free(str->c_string);
	free(str);
}

void test_string_init_c_string()
{
	size_t i = 0u;

	const char *str_const0 = "Hello, World!";
	String *str0 = string_init_c_string(str_const0);

	CU_ASSERT(str0->size == 13u);
	CU_ASSERT(str0->capacity == 14u);

	for (i = 0u; i < 13u; i++) {
		CU_ASSERT_EQUAL(str_const0[i], str0->c_string[i]);
	}
	printf("test_string_init_c_string print-0: %s\n", str0->c_string);

	free(str0->c_string);
	free(str0);

	// Tests empty string - Joan
	const char *str_const1 = "";
	String *str1 = string_init_c_string(str_const1);

	CU_ASSERT(str1->size == 0u);
	CU_ASSERT(str1->capacity == 1u);

	printf("test_string_init_c_string print-1: %s\n", str1->c_string);

	free(str1->c_string);
	free(str1);

	// Tests single character string - Joan
	const char *str_const2 = "l";
	String *str2 = string_init_c_string(str_const2);

	CU_ASSERT(str2->size == 1u);
	CU_ASSERT(str2->capacity == 2u);

	printf("test_string_init_c_string print-2: %s\n", str2->c_string);

	free(str2->c_string);
	free(str2);
}

void test_string_compare()
{
	String *l_str0 = string_init_c_string("");
	String *r_str0 = string_init_c_string("");
	CU_ASSERT(string_compare(l_str0, r_str0) == 1u);

	string_destroy(l_str0);
	string_destroy(r_str0);

	String *l_str1 = string_init_c_string("a");
	String *r_str1 = string_init_c_string("b");
	CU_ASSERT(string_compare(l_str1, r_str1) == 0u);

	string_destroy(l_str1);
	string_destroy(r_str1);

	String *l_str2 = string_init_c_string("a");
	String *r_str2 = string_init_c_string("a");
	CU_ASSERT(string_compare(l_str2, r_str2) == 1u);

	string_destroy(l_str2);
	string_destroy(r_str2);

	String *l_str3 = string_init_c_string("fgh");
	String *r_str3 = string_init_c_string("lks");
	CU_ASSERT(string_compare(l_str3, r_str3) == 0u);

	string_destroy(l_str3);
	string_destroy(r_str3);

	String *l_str4 = string_init_c_string("gbk");
	String *r_str4 = string_init_c_string("gbk");
	CU_ASSERT(string_compare(l_str4, r_str4) == 1u);

	string_destroy(l_str4);
	string_destroy(r_str4);

	String *l_str5 = string_init_c_string("lkjsdfnmx");
	String *r_str5 = string_init_c_string("lsdmflkjf");
	CU_ASSERT(string_compare(l_str5, r_str5) == 0u);

	string_destroy(l_str5);
	string_destroy(r_str5);

	String *l_str6 = string_init_c_string("string_init_equals");
	String *r_str6 = string_init_c_string("string_init_equals");
	CU_ASSERT(string_compare(l_str6, r_str6) == 1u);

	string_destroy(l_str6);
	string_destroy(r_str6);
}

void test_string_at()
{
	char c = '\0';
	// // empty string by c_string // //
	String *str0 = string_init_c_string("");

	c = string_at(str0, 0);
	CU_ASSERT(c == '\0');

	c = string_at(str0, 23426);
	CU_ASSERT(c == '\0');
	string_destroy(str0);

	// // emptry string by default // //
	String *str1 = string_init_default();

	c = string_at(str1, 0);
	CU_ASSERT(c == '\0');

	c = string_at(str1, 8678);
	CU_ASSERT(c == '\0');
	string_destroy(str1);

	// // single character string // //
	String *str2 = string_init_c_string("J");

	c = string_at(str2, 0);
	CU_ASSERT(c == 'J');

	c = string_at(str2, 1);
	CU_ASSERT(c == '\0');

	c = string_at(str2, 56756);
	CU_ASSERT(c == '\0');

	string_destroy(str2);

	// // double character string // //
	String *str3 = string_init_c_string("fL");

	c = string_at(str3, 0);
	CU_ASSERT(c == 'f');

	c = string_at(str3, 1);
	CU_ASSERT(c == 'L');

	c = string_at(str3, 2);
	CU_ASSERT(c == '\0');

	string_destroy(str3);
}

void test_string_pop_back()
{
	char c = '\0';

	// Empty string //
	String *str0 = string_init_default();

	c = string_pop_back(str0);
	CU_ASSERT(c == '\0');

	string_destroy(str0);

	// Single character string //
	String *str1 = string_init_c_string("k");

	c = string_pop_back(str1);
	CU_ASSERT(c == 'k');
	CU_ASSERT(str1->size == 0u);

	// double pop error
	c = string_pop_back(str1);
	CU_ASSERT(c == '\0');
	CU_ASSERT(str1->size == 0u);

	string_destroy(str1);

	// multi character string //
	String *str2 = string_init_c_string("abcd");

	c = string_pop_back(str2);
	CU_ASSERT(c == 'd');
	CU_ASSERT(str2->size == 3u);

	c = string_pop_back(str2);
	CU_ASSERT(c == 'c');
	CU_ASSERT(str2->size == 2u);

	c = string_pop_back(str2);
	CU_ASSERT(c == 'b');
	CU_ASSERT(str2->size == 1u);

	c = string_pop_back(str2);
	CU_ASSERT(c == 'a');
	CU_ASSERT(str2->size == 0u);

	c = string_pop_back(str2);
	CU_ASSERT(c == '\0');
	CU_ASSERT(str2->size == 0u);

	string_destroy(str2);
}

void test_string_append_char()
{
	char c = '\0';
	size_t r = 0u;

	// empty string //
	String *str0 = string_init_default();
	CU_ASSERT(str0->size == 0);

	r = string_append_char(str0, 'x');
	CU_ASSERT(str0->size == 1u);
	CU_ASSERT(r == 1u);
	c = string_at(str0, 0);
	CU_ASSERT(c == 'x');

	string_destroy(str0);

	// max capacitied string //
	String *str1 = string_init_c_string("abcdef");
	r = string_append_char(str1, 'g');
	CU_ASSERT(r == 1u);
	CU_ASSERT(str1->size == 7u);
	CU_ASSERT(str1->capacity == 14u);

	string_destroy(str1);
}