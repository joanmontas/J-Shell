// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#ifndef TEST_LEXER_H
#define TEST_LEXER_H
#include <stdio.h>
#include <CUnit/Basic.h>
#include "../../Lexer/Lexer.h"

// initializer
void test_lexer_init();
// helpers
void test_lexer_next_character();
void test_lexer_eat_white_space();
// actual lexing
void test_lexer_next_token_IDENT();
void test_lexer_next_token_QUOTED();
void test_lexer_next_token_QUOTED_ERROR();
void test_lexer_next_token_SYMBOL();

#endif