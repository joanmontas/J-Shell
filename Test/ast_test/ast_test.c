// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#include "ast_test.h"
#include <CUnit/CUError.h>
#include <CUnit/CUnit.h>

void test_ast_init()
{
	Command_Ast *comm =
		(Command_Ast *)Ast_init_factory(AST_COMMAND_TYPE, "asd");
	Binary_ast *bin = (Binary_ast *)Ast_init_factory(AST_BINARY_TYPE, "|");
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
	Binary_ast *bin = (Binary_ast *)Ast_init_factory(AST_BINARY_TYPE, "|");
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
	CU_ASSERT(strcmp(ast->ast_type, AST_BINARY_TYPE) == 0);

	ast = list_get_nth(&prog->commands, 2u);
	CU_ASSERT(strcmp(ast->ast_type, AST_IDENT_TYPE) == 0);

	ast = list_get_nth(&prog->commands, 3u);
	CU_ASSERT(strcmp(ast->ast_type, AST_QUOTED_TYPE) == 0);

	ast_destroy((Ast *)prog);
}

void test_ast_init_program_and_command()
{
	Ast *ast = NULL;

	Command_Ast *comm =
		(Command_Ast *)Ast_init_factory(AST_COMMAND_TYPE, "asd");
	Binary_ast *bin = (Binary_ast *)Ast_init_factory(AST_BINARY_TYPE, "|");
	Ident_Ast *id = (Ident_Ast *)Ast_init_factory(AST_IDENT_TYPE, "ls");
	Quoted_Ast *qted =
		(Quoted_Ast *)Ast_init_factory(AST_QUOTED_TYPE, "ls");

	Program_Ast *prog =
		(Program_Ast *)Ast_init_factory(AST_PROGRAM_TYPE, NULL);

	list_append(&prog->commands, comm);
	list_append(&comm->args, bin);
	list_append(&comm->args, id);
	list_append(&prog->commands, qted);

	ast = list_get_nth(&prog->commands, 0u);
	CU_ASSERT(ast != NULL);
	CU_ASSERT(strcmp(ast->ast_type, AST_COMMAND_TYPE) == 0);

	ast = list_get_nth(&prog->commands, 0u);
	CU_ASSERT(ast != NULL);
	CU_ASSERT(strcmp(ast->ast_type, AST_COMMAND_TYPE) == 0);
	comm = (Command_Ast *)ast;
	CU_ASSERT(comm->args.size == 2u);

	ast = list_get_nth(&comm->args, 0u);
	CU_ASSERT(ast != NULL);
	CU_ASSERT(strcmp(ast->ast_type, AST_BINARY_TYPE) == 0);
	ast = list_get_nth(&comm->args, 1u);
	CU_ASSERT(ast != NULL);
	CU_ASSERT(strcmp(ast->ast_type, AST_IDENT_TYPE) == 0);

	ast = list_get_nth(&prog->commands, 1u);
	CU_ASSERT(ast != NULL);
	CU_ASSERT(strcmp(ast->ast_type, AST_QUOTED_TYPE) == 0);

	ast_destroy((Ast *)prog);
}

void test_ast_init_program_and_path()
{
	Ast *ast = NULL;

	Program_Ast *prog =
		(Program_Ast *)Ast_init_factory(AST_PROGRAM_TYPE, NULL);
	Path_Ast *path = (Path_Ast *)Ast_init_factory(
		AST_PATH_TYPE,
		"../../kljsdf_234_fLKJSDf/asjsad14_34_23445dfsdfLKJAS/");
	Ident_Ast *id0 = (Ident_Ast *)Ast_init_factory(AST_IDENT_TYPE, "foo0");
	Ident_Ast *id1 =
		(Ident_Ast *)Ast_init_factory(AST_IDENT_TYPE, "sdfk_2hx4s");
	Quoted_Ast *qtd0 = (Quoted_Ast *)Ast_init_factory(
		AST_QUOTED_TYPE, "asdj! sdhjds f345fsd");

	list_append(&prog->commands, (void *)path);

	list_append(&path->args, (void *)id0);
	list_append(&path->args, (void *)id1);
	list_append(&path->args, (void *)qtd0);

	CU_ASSERT(prog->commands.size == 1u);

	ast = list_get_nth(&prog->commands, 0u);
	CU_ASSERT(ast != NULL);
	CU_ASSERT(ast_is_type(ast, AST_PATH_TYPE));

	CU_ASSERT(path->args.size == 3u);

	ast = list_get_nth(&path->args, 0u);
	CU_ASSERT(ast != NULL);
	CU_ASSERT(ast_is_type(ast, AST_IDENT_TYPE));
	id0 = (Ident_Ast *)ast;
	CU_ASSERT(strcmp(string_get_c_string(id0->value), "foo0") == 0);

	ast = list_get_nth(&path->args, 1u);
	CU_ASSERT(ast != NULL);
	CU_ASSERT(ast_is_type(ast, AST_IDENT_TYPE));
	id0 = (Ident_Ast *)ast;
	CU_ASSERT(strcmp(string_get_c_string(id0->value), "sdfk_2hx4s") == 0);

	ast = list_get_nth(&path->args, 2u);
	CU_ASSERT(ast != NULL);
	CU_ASSERT(ast_is_type(ast, AST_QUOTED_TYPE));
	qtd0 = (Quoted_Ast *)ast;
	CU_ASSERT(strcmp(string_get_c_string(qtd0->value),
			 "asdj! sdhjds f345fsd") == 0);

	ast_destroy((Ast *)prog);
}