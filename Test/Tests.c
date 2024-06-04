
// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#include <stdio.h>
#include <time.h>
#include <CUnit/Basic.h>

#include "./string_test/string_test.h"

int main()
{
	srand((unsigned int)time(NULL));

	CU_initialize_registry();

	// test_string
	CU_pSuite test_string_suite =
		CU_add_suite("string testing", NULL, NULL);
	CU_add_test(test_string_suite, "Test default string initialization",
		    test_string_init_default);
	CU_add_test(
		test_string_suite,
		"Test string initialization from c_string with different sizes",
		test_string_init_c_string);
	CU_add_test(test_string_suite,
		    "Test string comparison with different sizes",
		    test_string_compare);
	CU_add_test(test_string_suite, "Test string at with different sizes",
		    test_string_at);
	CU_add_test(test_string_suite,
		    "Test string pop back with different sizes",
		    test_string_pop_back);
	CU_add_test(test_string_suite, "Test string append char",
		    test_string_append_char);


	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
