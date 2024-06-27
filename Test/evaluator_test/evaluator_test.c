// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#include "evaluator_test.h"
#include <CUnit/CUnit.h>

void test_eval_single_argument_Ident_formatter()
{
	char *str0 = "ls ..;";
	Lexer l = Lexer_init(str0);
	Parser p = Parser_init(&l);

	Ast *tree = Parse(&p);

	CU_ASSERT(tree != NULL);

	Program_Ast *prog = (Program_Ast *)tree;
	CU_ASSERT(prog->commands.size == 1u);
	Ast *comm = list_get_nth(&prog->commands, 0u);

	Cmd_Args_format *caf = cmd_and_arg_formater(comm);
	CU_ASSERT(strcmp(caf->cmd, "/bin/ls") == 0);
	CU_ASSERT(strcmp(caf->args[0], "/bin/ls") == 0);
	CU_ASSERT(strcmp(caf->args[1], "..") == 0);
	cmd_args_destroy(caf);

	ast_destroy(tree);
	parser_destroy(&p);
	lexer_destroy(&l);
}

void test_eval_single_argument_Path_formatter()
{
	char *str0 = "./my-exec ..;";
	Lexer l = Lexer_init(str0);
	Parser p = Parser_init(&l);

	Ast *tree = Parse(&p);

	CU_ASSERT(tree != NULL);

	Program_Ast *prog = (Program_Ast *)tree;
	CU_ASSERT(prog->commands.size == 1u);
	Ast *comm = list_get_nth(&prog->commands, 0u);

	Cmd_Args_format *caf = cmd_and_arg_formater(comm);
	CU_ASSERT(strcmp(caf->cmd, "./my-exec") == 0);
	CU_ASSERT(strcmp(caf->args[0], "./my-exec") == 0);
	CU_ASSERT(strcmp(caf->args[1], "..") == 0);
	cmd_args_destroy(caf);

	ast_destroy(tree);
	parser_destroy(&p);
	lexer_destroy(&l);
}

void test_eval_evaluating_single_argument_ident()
{
	int original_fd[2];
	CU_ASSERT(pipe(original_fd) != -1);

	char *str0 = "echo hi;";
	Lexer l = Lexer_init(str0);
	Parser p = Parser_init(&l);

	Ast *tree = Parse(&p);

	CU_ASSERT(tree != NULL);

	int rslt = Evaluate((Program_Ast *)tree, original_fd);
	CU_ASSERT(rslt != -1);

	close(original_fd[WRITE_END]);

	char buffer[1024];
	ssize_t bytes_read =
		read(original_fd[READ_END], buffer, sizeof(buffer) - 1);
	if (bytes_read > 0) {
		buffer[bytes_read] = '\0';
		printf("%s", buffer);
	}
	CU_ASSERT(strcmp(buffer, "hi\n") == 0);
	close(original_fd[READ_END]);

	ast_destroy(tree);
	parser_destroy(&p);
	lexer_destroy(&l);
}

void test_eval_evaluating_single_argument_path()
{
	int original_fd[2];
	CU_ASSERT(pipe(original_fd) != -1);

	char *str0 = "./hello-world.sh;";
	Lexer l = Lexer_init(str0);
	Parser p = Parser_init(&l);

	Ast *tree = Parse(&p);

	CU_ASSERT(tree != NULL);

	int rslt = Evaluate((Program_Ast *)tree, original_fd);
	CU_ASSERT(rslt != -1);

	close(original_fd[WRITE_END]);

	char buffer[1024];
	ssize_t bytes_read =
		read(original_fd[READ_END], buffer, sizeof(buffer) - 1);
	if (bytes_read > 0) {
		buffer[bytes_read] = '\0';
		printf("%s", buffer);
	}
	CU_ASSERT(strcmp(buffer, "hi\n") == 0);
	close(original_fd[READ_END]);

	ast_destroy(tree);
	parser_destroy(&p);
	lexer_destroy(&l);
}