// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#ifndef TEST_EVALUATOR_H
#define TEST_EVALUATOR_H
#include <CUnit/Basic.h>
#include "../../Evaluator/Evaluator.h"
#include "../../Lexer/Lexer.h"
#include "../../Parser/Parser.h"

// eval
void test_eval_evaluating_single_argument_ident();
void test_eval_evaluating_single_argument_path();
// helpers
void test_eval_single_argument_Ident_formatter();
void test_eval_single_argument_Path_formatter();

#endif