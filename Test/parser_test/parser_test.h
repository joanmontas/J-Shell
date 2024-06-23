// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#ifndef TEST_PARSER_H
#define TEST_PARSER_H
#include <stdio.h>
#include <CUnit/Basic.h>
#include "../../Parser/Parser.h"
// initializer
void test_parser_init();
void test_parser_next_token();
void test_parser_single_command_parse();
void test_parser_single_path_parse();
void test_parser_single_quote_as_argument_parse();
void test_parser_single_path_as_argument_parse();
void test_parser_binary_command_parse();
#endif