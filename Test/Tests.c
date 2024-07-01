
// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#include <stdio.h>
#include <time.h>
#include <CUnit/Basic.h>

#include "./string_test/string_test.h"
#include "./hash_table_test/hash_table_test.h"
#include "./list_test/list_test.h"
#include "./token_test/token_test.h"
#include "./lexer_test/lexer_test.h"
#include "./ast_test/ast_test.h"
#include "./parser_test/parser_test.h"
#include "./evaluator_test/evaluator_test.h"

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

	// test list
	CU_pSuite test_list_suite = CU_add_suite("List testing", NULL, NULL);
	CU_add_test(test_list_suite, "Test list initialization",
		    test_list_init);
	CU_add_test(test_list_suite, "Test list append", test_list_append);
	CU_add_test(test_list_suite, "Test list append with destructor pattern",
		    test_list_append_smart_pointer);
	CU_add_test(test_list_suite, "Test list delete ith",
		    test_list_delete_nth);
	CU_add_test(test_list_suite,
		    "Test list delete ith with destructor pattern",
		    test_list_delete_nth_smart_pointer);
	CU_add_test(test_list_suite, "Test single list delete ith",
		    test_list_delete_nth_single_node_list);
	CU_add_test(test_list_suite, "Test double list delete ith",
		    test_list_delete_nth_double_node_list);
	CU_add_test(test_list_suite, "Test triple list delete ith",
		    test_list_delete_nth_triple_node_list);
	CU_add_test(test_list_suite, "Test list get ith",
		    test_list_get_nth_empty_list);
	CU_add_test(test_list_suite, "Test single list get ith",
		    test_list_get_nth_single_list);
	CU_add_test(test_list_suite, "Test double list get ith",
		    test_list_get_nth_double_list);
	CU_add_test(test_list_suite, "Test triple list get ith",
		    test_list_get_nth_triple_list);
	CU_add_test(test_list_suite, "Test linear search equality function",
		    test_list_linear_search_exist);

	// test hash_table
	CU_pSuite test_hash_table_suite =
		CU_add_suite("Hash_table testing", NULL, NULL);
	CU_add_test(test_hash_table_suite, "Test hash initialization",
		    test_hash_table_init);
	CU_add_test(test_hash_table_suite, "Test hash insertion",
		    test_hash_table_insert);

	// test_token
	CU_pSuite test_token_suite = CU_add_suite("token testing", NULL, NULL);
	CU_add_test(test_token_suite, "Test token reset", test_token_reset);

	// test_lexer
	CU_pSuite test_lexer_suite = CU_add_suite("lexer testing", NULL, NULL);
	CU_add_test(test_lexer_suite, "Test default lexer initialization",
		    test_lexer_init);

	CU_add_test(test_lexer_suite,
		    "Test lexer next character with different sizes",
		    test_lexer_next_character);

	CU_add_test(test_lexer_suite,
		    "Test lexer eat white with different sizes",
		    test_lexer_eat_white_space);

	CU_add_test(
		test_lexer_suite,
		"Test lexer next token white with idents of different sizes",
		test_lexer_eat_white_space);

	CU_add_test(test_lexer_suite,
		    "Test lexer next token with ident of different sizes",
		    test_lexer_next_token_IDENT);

	CU_add_test(
		test_lexer_suite,
		"Test lexer next token with quoted token of different sizes",
		test_lexer_next_token_QUOTED);

	CU_add_test(
		test_lexer_suite,
		"Test lexer next token with unclosed quoted token of different sizes",
		test_lexer_next_token_QUOTED_ERROR);

	CU_add_test(
		test_lexer_suite,
		"Test lexer next token with symbol with input of different sizes",
		test_lexer_next_token_SYMBOL);

	CU_add_test(test_lexer_suite, "Test lexer next token with path",
		    test_lexer_next_token_PATH);

	// test ast
	CU_pSuite test_ast_suite = CU_add_suite("Ast testing", NULL, NULL);
	CU_add_test(test_ast_suite,
		    "Test parser initialization and destruction",
		    test_ast_init);
	CU_add_test(test_ast_suite,
		    "Test parser initialization and destruction",
		    test_ast_init_program);
	CU_add_test(test_ast_suite,
		    "Test parser initialization and destruction",
		    test_ast_init_program_and_command);
	CU_add_test(test_ast_suite,
		    "Test parser initialization and destruction of path",
		    test_ast_init_program_and_path);

	// test parser
	CU_pSuite test_parser_suite =
		CU_add_suite("Parser testing", NULL, NULL);
	CU_add_test(test_parser_suite, "Test parser initialization",
		    test_parser_init);
	CU_add_test(test_parser_suite, "Test parser next token",
		    test_parser_next_token);
	CU_add_test(test_parser_suite, "Test parser single parse of command",
		    test_parser_single_command_parse);
	CU_add_test(test_parser_suite, "Test parser single parse of path",
		    test_parser_single_path_parse);
	CU_add_test(test_parser_suite,
		    "Test parser command single quote argument parse",
		    test_parser_single_quote_as_argument_parse);
	CU_add_test(test_parser_suite,
		    "Test parser command single path argument parse",
		    test_parser_single_path_as_argument_parse);
	CU_add_test(test_parser_suite, "Test parser single binary",
		    test_parser_binary_command_parse);

	// test evaluator
	CU_pSuite test_evaluator_suite =
		CU_add_suite("Evaluator testing", NULL, NULL);
	CU_add_test(test_evaluator_suite,
		    "Test command argument formater for ident",
		    test_eval_single_argument_Ident_formatter);
	CU_add_test(test_evaluator_suite,
		    "Test command argument formatter for ident",
		    test_eval_single_argument_Path_formatter);
	CU_add_test(test_evaluator_suite,
		    "Test evaluation of single command ident",
		    test_eval_evaluating_single_argument_ident);
	CU_add_test(test_evaluator_suite,
		    "Test evaluation of single command path",
		    test_eval_evaluating_single_argument_path);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
