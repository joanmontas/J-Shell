// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#include "token_test.h"

void test_token_reset()
{
	String *s0 = string_init_c_string(TOKEN_IDENT_TYPE);
	String *s1 = string_init_c_string("my_var");

	Token t0 = { s0, s1 };

	token_reset(&t0);

	CU_ASSERT(t0.token_type == NULL);
	CU_ASSERT(t0.literal == NULL);

	Token t1 = { NULL, NULL };

	token_reset(&t1);

	CU_ASSERT(t1.token_type == NULL);
	CU_ASSERT(t1.literal == NULL);
}