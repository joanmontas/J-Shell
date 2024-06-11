// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#include "lexer_test.h"
#include <CUnit/CUnit.h>
#include <string.h>

void test_lexer_init()
{
	// empty string //
	char *input_str0 = "";
	Lexer l0 = Lexer_init(input_str0);

	CU_ASSERT(l0.position == 0u);
	CU_ASSERT(l0.input_size == 0u);
	CU_ASSERT(l0.current_char == '\0');

	lexer_destroy(&l0);

	// multi character string //
	char *input_str1 = "ls path";
	Lexer l1 = Lexer_init(input_str1);

	CU_ASSERT(l1.position == 0u);
	CU_ASSERT(l1.input_size == 7u);
	CU_ASSERT(l1.current_char == 'l');
	lexer_destroy(&l1);

	char *input_str2 = NULL;
	Lexer l2 = Lexer_init(input_str2);

	// NULL //

	CU_ASSERT(l2.position == 0u);
	CU_ASSERT(l2.input_size == 0u);
	CU_ASSERT(l2.current_char == '\0');
	lexer_destroy(&l2);
}

void test_lexer_next_character()
{
	// next character on empty string //
	char *input_str0 = "";
	Lexer l0 = Lexer_init(input_str0);

	lexer_next_character(&l0);

	CU_ASSERT(l0.position == 0u);
	CU_ASSERT(l0.input_size == 0u);
	CU_ASSERT(l0.current_char == '\0');

	lexer_destroy(&l0);

	// multi string //
	char *input_str1 = "tres";
	Lexer l1 = Lexer_init(input_str1);

	CU_ASSERT(l1.input_size == 4u);

	CU_ASSERT(l1.position == 0u);
	CU_ASSERT(l1.current_char == 't');

	lexer_next_character(&l1);
	CU_ASSERT(l1.position == 1u);
	CU_ASSERT(l1.current_char == 'r');

	lexer_next_character(&l1);
	CU_ASSERT(l1.position == 2u);
	CU_ASSERT(l1.current_char == 'e');

	lexer_next_character(&l1);
	CU_ASSERT(l1.position == 3u);
	CU_ASSERT(l1.current_char == 's');

	lexer_next_character(&l1);
	CU_ASSERT(l1.position == 3u);
	CU_ASSERT(l1.current_char == '\0');

	lexer_destroy(&l1);

	// NULL //
	char *input_str2 = NULL;
	Lexer l2 = Lexer_init(input_str2);

	lexer_next_character(&l2);

	CU_ASSERT(l2.position == 0u);
	CU_ASSERT(l2.input_size == 0u);
	CU_ASSERT(l2.current_char == '\0');

	lexer_destroy(&l2);
}

void test_lexer_eat_white_space()
{
	// empty string //
	char *input_str0 = "";
	Lexer l0 = Lexer_init(input_str0);

	lexer_eat_white_space(&l0);

	CU_ASSERT(l0.position == 0u);
	CU_ASSERT(l0.input_size == 0u);
	CU_ASSERT(l0.current_char == '\0');

	lexer_destroy(&l0);

	// multi character //
	char *input_str1 = " ABCDEF1";
	Lexer l1 = Lexer_init(input_str1);

	lexer_eat_white_space(&l1);

	CU_ASSERT(l1.position == 1u);
	CU_ASSERT(l1.input_size == 8u);
	CU_ASSERT(l1.current_char == 'A');

	lexer_destroy(&l1);
}

void test_lexer_next_token_IDENT()
{
	// empty string //
	char *input_str0 = "";
	Lexer l0 = Lexer_init(input_str0);

	CU_ASSERT(token_is_type(&l0.current_token, TOKEN_NONE_TYPE));
	CU_ASSERT(token_is_type(&l0.peek_token, TOKEN_NONE_TYPE));

	CU_ASSERT(l0.position == 0u);
	CU_ASSERT(l0.input_size == 0u);
	CU_ASSERT(l0.current_char == '\0');

	lexer_next_token(&l0);
	CU_ASSERT(token_is_type(&l0.current_token, TOKEN_NONE_TYPE));
	CU_ASSERT(token_is_type(&l0.peek_token, TOKEN_EOF_TYPE));

	lexer_next_token(&l0);
	CU_ASSERT(token_is_type(&l0.current_token, TOKEN_EOF_TYPE));
	CU_ASSERT(token_is_type(&l0.peek_token, TOKEN_EOF_TYPE));

	lexer_destroy(&l0);

	// single number "1";
	char *input_str1 = "1";
	Lexer l1 = Lexer_init(input_str1);

	CU_ASSERT(token_is_type(&l1.current_token, TOKEN_NONE_TYPE));
	CU_ASSERT(token_is_type(&l1.peek_token, TOKEN_NONE_TYPE));

	CU_ASSERT(l1.position == 0u);
	CU_ASSERT(l1.input_size == 1u);
	CU_ASSERT(l1.current_char == '1');

	lexer_next_token(&l1);
	CU_ASSERT(token_is_type(&l1.current_token, TOKEN_NONE_TYPE));
	CU_ASSERT(token_is_type(&l1.peek_token, TOKEN_IDENT_TYPE));
	CU_ASSERT(strcmp(l1.peek_token.literal->c_string, "1") == 0);

	lexer_next_token(&l1);
	CU_ASSERT(token_is_type(&l1.current_token, TOKEN_IDENT_TYPE));
	CU_ASSERT(token_is_type(&l1.peek_token, TOKEN_EOF_TYPE));

	lexer_next_token(&l1);
	CU_ASSERT(token_is_type(&l1.current_token, TOKEN_EOF_TYPE));
	CU_ASSERT(token_is_type(&l1.peek_token, TOKEN_EOF_TYPE));

	lexer_destroy(&l1);

	// multi digit number //

	char *input_str2 = "54";
	Lexer l2 = Lexer_init(input_str2);
	CU_ASSERT(token_is_type(&l2.current_token, TOKEN_NONE_TYPE));
	CU_ASSERT(token_is_type(&l2.peek_token, TOKEN_NONE_TYPE));

	lexer_next_token(&l2);
	CU_ASSERT(token_is_type(&l2.current_token, TOKEN_NONE_TYPE));
	CU_ASSERT(token_is_type(&l2.peek_token, TOKEN_IDENT_TYPE));
	CU_ASSERT(strcmp(l2.peek_token.literal->c_string, "54") == 0);

	lexer_next_token(&l2);
	CU_ASSERT(token_is_type(&l2.current_token, TOKEN_IDENT_TYPE));
	CU_ASSERT(token_is_type(&l2.peek_token, TOKEN_EOF_TYPE));

	lexer_next_token(&l2);
	CU_ASSERT(token_is_type(&l2.current_token, TOKEN_EOF_TYPE));
	CU_ASSERT(token_is_type(&l2.peek_token, TOKEN_EOF_TYPE));

	lexer_destroy(&l2);

	// multi numbers //
	char *input_str3 = "8304 56";
	Lexer l3 = Lexer_init(input_str3);
	CU_ASSERT(token_is_type(&l3.current_token, TOKEN_NONE_TYPE));
	CU_ASSERT(token_is_type(&l3.peek_token, TOKEN_NONE_TYPE));

	lexer_next_token(&l3);
	CU_ASSERT(token_is_type(&l3.current_token, TOKEN_NONE_TYPE));
	CU_ASSERT(token_is_type(&l3.peek_token, TOKEN_IDENT_TYPE));
	CU_ASSERT(strcmp(l3.peek_token.literal->c_string, "8304") == 0);

	lexer_next_token(&l3);
	CU_ASSERT(token_is_type(&l3.current_token, TOKEN_IDENT_TYPE));
	CU_ASSERT(token_is_type(&l3.peek_token, TOKEN_IDENT_TYPE));
	CU_ASSERT(strcmp(l3.peek_token.literal->c_string, "56") == 0);

	lexer_destroy(&l3);

	// complex ident //;
	char *input_str4 = "9873456sdfsd";
	Lexer l4 = Lexer_init(input_str4);
	CU_ASSERT(token_is_type(&l4.current_token, TOKEN_NONE_TYPE));
	CU_ASSERT(token_is_type(&l4.peek_token, TOKEN_NONE_TYPE));

	lexer_next_token(&l4);
	CU_ASSERT(token_is_type(&l4.current_token, TOKEN_NONE_TYPE));
	CU_ASSERT(token_is_type(&l4.peek_token, TOKEN_IDENT_TYPE));
	CU_ASSERT(strcmp(l4.peek_token.literal->c_string, "9873456sdfsd") == 0);

	lexer_next_token(&l4);
	CU_ASSERT(token_is_type(&l4.current_token, TOKEN_IDENT_TYPE));
	CU_ASSERT(token_is_type(&l4.peek_token, TOKEN_EOF_TYPE));
	CU_ASSERT(strcmp(l4.current_token.literal->c_string, "9873456sdfsd") ==
		  0);

	lexer_next_token(&l4);
	CU_ASSERT(token_is_type(&l4.current_token, TOKEN_EOF_TYPE));
	CU_ASSERT(token_is_type(&l4.peek_token, TOKEN_EOF_TYPE));

	lexer_destroy(&l4);
}

void test_lexer_next_token_QUOTED()
{
	// empty quote //
	char *input_str0 = "\"\"";
	Lexer l0 = Lexer_init(input_str0);

	CU_ASSERT(token_is_type(&l0.current_token, TOKEN_NONE_TYPE));
	CU_ASSERT(token_is_type(&l0.peek_token, TOKEN_NONE_TYPE));

	lexer_next_token(&l0);
	CU_ASSERT(token_is_type(&l0.current_token, TOKEN_NONE_TYPE));
	CU_ASSERT(token_is_type(&l0.peek_token, TOKEN_QUOTED_TYPE));
	CU_ASSERT(l0.peek_token.literal->size == 0u);
	CU_ASSERT(strcmp(l0.peek_token.literal->c_string, "") == 0);

	lexer_next_token(&l0);
	CU_ASSERT(token_is_type(&l0.current_token, TOKEN_QUOTED_TYPE));
	CU_ASSERT(token_is_type(&l0.peek_token, TOKEN_EOF_TYPE));
	CU_ASSERT(l0.current_token.literal->size == 0u);

	lexer_next_token(&l0);
	CU_ASSERT(token_is_type(&l0.current_token, TOKEN_EOF_TYPE));
	CU_ASSERT(token_is_type(&l0.peek_token, TOKEN_EOF_TYPE))

	lexer_destroy(&l0);

	// single characters quoted //
	char *input_str1 = "\"V\"";
	Lexer l1 = Lexer_init(input_str1);

	CU_ASSERT(token_is_type(&l1.current_token, TOKEN_NONE_TYPE));
	CU_ASSERT(token_is_type(&l1.peek_token, TOKEN_NONE_TYPE));

	lexer_next_token(&l1);
	CU_ASSERT(token_is_type(&l1.current_token, TOKEN_NONE_TYPE));
	CU_ASSERT(token_is_type(&l1.peek_token, TOKEN_QUOTED_TYPE));
	CU_ASSERT(strcmp(l1.peek_token.literal->c_string, "V") == 0);

	lexer_next_token(&l1);
	CU_ASSERT(token_is_type(&l1.current_token, TOKEN_QUOTED_TYPE));
	CU_ASSERT(token_is_type(&l1.peek_token, TOKEN_EOF_TYPE));

	lexer_next_token(&l1);
	CU_ASSERT(token_is_type(&l1.current_token, TOKEN_EOF_TYPE));
	CU_ASSERT(token_is_type(&l1.peek_token, TOKEN_EOF_TYPE));

	lexer_destroy(&l1);

	// double character quoted //
	char *input_str2 = "\"d8\"";
	Lexer l2 = Lexer_init(input_str2);

	CU_ASSERT(token_is_type(&l2.current_token, TOKEN_NONE_TYPE));
	CU_ASSERT(token_is_type(&l2.peek_token, TOKEN_NONE_TYPE));

	lexer_next_token(&l2);
	CU_ASSERT(token_is_type(&l2.current_token, TOKEN_NONE_TYPE));
	CU_ASSERT(token_is_type(&l2.peek_token, TOKEN_QUOTED_TYPE));
	CU_ASSERT(l2.peek_token.literal->size == 2u);
	CU_ASSERT(strcmp(l2.peek_token.literal->c_string, "d8") == 0);

	lexer_next_token(&l2);
	CU_ASSERT(token_is_type(&l2.current_token, TOKEN_QUOTED_TYPE));
	CU_ASSERT(token_is_type(&l2.peek_token, TOKEN_EOF_TYPE));

	lexer_next_token(&l2);
	CU_ASSERT(token_is_type(&l2.current_token, TOKEN_EOF_TYPE));
	CU_ASSERT(token_is_type(&l2.peek_token, TOKEN_EOF_TYPE));

	lexer_destroy(&l2);

	// triple character quoted //
	char *input_str3 = "\"&X0\"";
	Lexer l3 = Lexer_init(input_str3);

	CU_ASSERT(token_is_type(&l3.current_token, TOKEN_NONE_TYPE));
	CU_ASSERT(token_is_type(&l3.peek_token, TOKEN_NONE_TYPE));

	lexer_next_token(&l3);
	CU_ASSERT(token_is_type(&l3.current_token, TOKEN_NONE_TYPE));
	CU_ASSERT(token_is_type(&l3.peek_token, TOKEN_QUOTED_TYPE));
	CU_ASSERT(l3.peek_token.literal->size == 3u);
	CU_ASSERT(strcmp(l3.peek_token.literal->c_string, "&X0") == 0);

	lexer_next_token(&l3);
	CU_ASSERT(token_is_type(&l3.current_token, TOKEN_QUOTED_TYPE));
	CU_ASSERT(strcmp(l3.current_token.literal->c_string, "&X0") == 0);
	CU_ASSERT(token_is_type(&l3.peek_token, TOKEN_EOF_TYPE));

	lexer_next_token(&l3);
	CU_ASSERT(token_is_type(&l3.current_token, TOKEN_EOF_TYPE));
	CU_ASSERT(token_is_type(&l3.peek_token, TOKEN_EOF_TYPE));

	lexer_destroy(&l3);
}

void test_lexer_next_token_SYMBOL()
{
	// single symbol //
	char *input_str0 = ";";
	Lexer l0 = Lexer_init(input_str0);

	CU_ASSERT(token_is_type(&l0.current_token, TOKEN_NONE_TYPE));
	CU_ASSERT(token_is_type(&l0.peek_token, TOKEN_NONE_TYPE));

	lexer_next_token(&l0);
	CU_ASSERT(token_is_type(&l0.current_token, TOKEN_NONE_TYPE));
	CU_ASSERT(token_is_type(&l0.peek_token, TOKEN_SYMBOL_TYPE));
	CU_ASSERT(strcmp(l0.peek_token.literal->c_string, ";") == 0);

	lexer_next_token(&l0);
	CU_ASSERT(token_is_type(&l0.current_token, TOKEN_SYMBOL_TYPE));
	CU_ASSERT(strcmp(l0.current_token.literal->c_string, ";") == 0);
	CU_ASSERT(token_is_type(&l0.peek_token, TOKEN_EOF_TYPE));

	lexer_next_token(&l0);
	CU_ASSERT(token_is_type(&l0.current_token, TOKEN_EOF_TYPE));
	CU_ASSERT(token_is_type(&l0.peek_token, TOKEN_EOF_TYPE));


	lexer_destroy(&l0);
}