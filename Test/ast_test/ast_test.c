// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#include "ast_test.h"
#include <CUnit/CUnit.h>
#include <string.h>

void test_ast_init()
{
	Command_Ast *comm =
		(Command_Ast *)Ast_init_factory(AST_COMMAND_TYPE, "asd");
	Binary_Ast *bin = (Binary_Ast *)Ast_init_factory(AST_SYMBOL_TYPE, "|");
	Ident_Ast *id = (Ident_Ast *)Ast_init_factory(AST_IDENT_TYPE, "ls");
	Quoted_Ast *qted =
		(Quoted_Ast *)Ast_init_factory(AST_QUOTED_TYPE, "ls");

	ast_destroy((Ast *)comm);
	ast_destroy((Ast *)bin);
	ast_destroy((Ast *)id);
	ast_destroy((Ast *)qted);
}

void test_ast_init_program()
{
	Ast *ast = NULL;

	Command_Ast *comm =
		(Command_Ast *)Ast_init_factory(AST_COMMAND_TYPE, "asd");
	Binary_Ast *bin = (Binary_Ast *)Ast_init_factory(AST_SYMBOL_TYPE, "|");
	Ident_Ast *id = (Ident_Ast *)Ast_init_factory(AST_IDENT_TYPE, "ls");
	Quoted_Ast *qted =
		(Quoted_Ast *)Ast_init_factory(AST_QUOTED_TYPE, "ls");

	Program_Ast *prog =
		(Program_Ast *)Ast_init_factory(AST_PROGRAM_TYPE, NULL);

	list_append(&prog->commands, comm);
	list_append(&prog->commands, bin);
	list_append(&prog->commands, id);
	list_append(&prog->commands, qted);

	ast = list_get_nth(&prog->commands, 0u);
	CU_ASSERT(strcmp(ast->ast_type, AST_COMMAND_TYPE) == 0);

	ast = list_get_nth(&prog->commands, 1u);
	CU_ASSERT(strcmp(ast->ast_type, AST_SYMBOL_TYPE) == 0);

	ast = list_get_nth(&prog->commands, 2u);
	CU_ASSERT(strcmp(ast->ast_type, AST_IDENT_TYPE) == 0);

	ast = list_get_nth(&prog->commands, 3u);
	CU_ASSERT(strcmp(ast->ast_type, AST_QUOTED_TYPE) == 0);

	ast_destroy((Ast *)prog);
}
