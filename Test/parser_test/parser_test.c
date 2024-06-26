// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#include "parser_test.h"
#include <CUnit/CUnit.h>
#include <string.h>

void test_parser_init()
{
	char *str0 = "\"Hello, World!\" kgsdas";
	Lexer l0 = Lexer_init(str0);
	Parser p0 = Parser_init(&l0);
	CU_ASSERT(p0.err == 0u);

	CU_ASSERT(token_is_type(p0.current_token, TOKEN_QUOTED_TYPE));
	CU_ASSERT(token_is_type(p0.peek_token, TOKEN_IDENT_TYPE));

	parser_destroy(&p0);
	lexer_destroy(&l0);

	// empty program

	char *str1 = "";
	Lexer l1 = Lexer_init(str1);
	Parser p1 = Parser_init(&l1);
	CU_ASSERT(p1.err == 0u);

	CU_ASSERT(token_is_type(p1.current_token, TOKEN_EOF_TYPE));
	CU_ASSERT(token_is_type(p1.peek_token, TOKEN_EOF_TYPE));

	parser_destroy(&p1);
	lexer_destroy(&l1);
}

void test_parser_next_token()
{
	char *str0 = "; 123 \"Hello, World!\" kgsdas";
	Lexer l0 = Lexer_init(str0);
	Parser p0 = Parser_init(&l0);
	CU_ASSERT(p0.err == 0u);

	CU_ASSERT(token_is_type(p0.current_token, TOKEN_SYMBOL_TYPE));
	CU_ASSERT(token_is_type(p0.peek_token, TOKEN_IDENT_TYPE));

	parser_next_token(&p0);
	CU_ASSERT(token_is_type(p0.current_token, TOKEN_IDENT_TYPE));
	CU_ASSERT(token_is_type(p0.peek_token, TOKEN_QUOTED_TYPE));

	parser_next_token(&p0);
	CU_ASSERT(token_is_type(p0.current_token, TOKEN_QUOTED_TYPE));
	CU_ASSERT(token_is_type(p0.peek_token, TOKEN_IDENT_TYPE));

	parser_next_token(&p0);
	CU_ASSERT(token_is_type(p0.current_token, TOKEN_IDENT_TYPE));
	CU_ASSERT(token_is_type(p0.peek_token, TOKEN_EOF_TYPE));

	parser_next_token(&p0);
	CU_ASSERT(token_is_type(p0.current_token, TOKEN_EOF_TYPE));
	CU_ASSERT(token_is_type(p0.peek_token, TOKEN_EOF_TYPE));

	parser_destroy(&p0);
	lexer_destroy(&l0);
}

void test_parser_single_command_parse()
{
	char *str = "hi;";
	Ast *tree = NULL;
	Ast *ast = NULL;
	Program_Ast *prog = NULL;
	Command_Ast *comm = NULL;

	Lexer l = Lexer_init(str);
	Parser p = Parser_init(&l);

	CU_ASSERT(p.err == 0u);

	tree = Parse(&p);
	CU_ASSERT(tree != NULL);
	CU_ASSERT(ast_is_type(tree, AST_PROGRAM_TYPE));

	prog = (Program_Ast *)tree;

	CU_ASSERT(prog->commands.size == 1u);

	ast = (Ast *)list_get_nth(&prog->commands, 0u);

	CU_ASSERT(ast_is_type(ast, AST_COMMAND_TYPE));
	comm = (Command_Ast *)ast;

	CU_ASSERT(comm->args.size == 0u);
	CU_ASSERT(strcmp(string_get_c_string(comm->value), "hi") == 0);

	ast_destroy(tree);
	parser_destroy(&p);
	lexer_destroy(&l);
}

void test_parser_single_quote_as_argument_parse()
{
	char *str = "ls \"some stuff here!\";";
	Ast *tree = NULL;
	Ast *ast = NULL;
	Program_Ast *prog = NULL;
	Command_Ast *comm = NULL;

	Lexer l = Lexer_init(str);
	Parser p = Parser_init(&l);

	CU_ASSERT(p.err == 0u);

	tree = Parse(&p);
	CU_ASSERT(tree != NULL);
	CU_ASSERT(ast_is_type(tree, AST_PROGRAM_TYPE));

	prog = (Program_Ast *)tree;

	CU_ASSERT(prog->commands.size == 1u);

	ast = (Ast *)list_get_nth(&prog->commands, 0u);

	CU_ASSERT(ast_is_type(ast, AST_COMMAND_TYPE));
	comm = (Command_Ast *)ast;

	CU_ASSERT(comm->args.size == 1u);
	CU_ASSERT(strcmp(string_get_c_string(comm->value), "ls") == 0);

	ast_destroy(tree);
	parser_destroy(&p);
	lexer_destroy(&l);
}

void test_parser_binary_command_parse()
{
	char *str = "hello | world;";
	Ast *tree = NULL;
	Ast *ast = NULL;

	Program_Ast *prog = NULL;
	Command_Ast *comm = NULL;
	Binary_Ast *bin = NULL;

	Lexer l = Lexer_init(str);
	Parser p = Parser_init(&l);

	CU_ASSERT(p.err == 0u);

	tree = Parse(&p);
	CU_ASSERT(tree != NULL);
	CU_ASSERT(ast_is_type(tree, AST_PROGRAM_TYPE));

	prog = (Program_Ast *)tree;

	CU_ASSERT(prog->commands.size == 1u);

	ast = (Ast *)list_get_nth(&prog->commands, 0u);

	CU_ASSERT(ast_is_type(ast, AST_SYMBOL_TYPE));
	bin = (Binary_Ast *)ast;

	CU_ASSERT(strcmp(string_get_c_string(bin->value), "|") == 0);

	comm = (Command_Ast *)bin->left;
	CU_ASSERT(strcmp(string_get_c_string(comm->value), "hello") == 0);
	CU_ASSERT(comm->args.size == 0u);

	comm = (Command_Ast *)bin->right;
	CU_ASSERT(strcmp(string_get_c_string(comm->value), "world") == 0);
	CU_ASSERT(comm->args.size == 0u);

	ast_destroy(tree);
	parser_destroy(&p);
	lexer_destroy(&l);
}

void test_parser_single_path_parse()
{
	// current path
	Ast *ast = NULL;
	Ast *tree = NULL;
	Path_Ast *pth = NULL;
	Program_Ast *prog = NULL;

	char *str0 = "  .       ;";
	Lexer l = Lexer_init(str0);
	Parser p = Parser_init(&l);

	tree = Parse(&p);
	CU_ASSERT(tree != NULL);
	CU_ASSERT(ast_is_type(tree, AST_PROGRAM_TYPE));
	prog = (Program_Ast *)tree;

	CU_ASSERT(prog->commands.size == 1u);
	ast = list_get_nth(&prog->commands, 0u);
	CU_ASSERT(ast != NULL);
	CU_ASSERT(ast_is_type(ast, AST_PATH_TYPE));

	pth = (Path_Ast *)ast;
	CU_ASSERT(pth->args.size == 0u);
	CU_ASSERT(strcmp(string_get_c_string(pth->value), ".") == 0);

	ast_destroy(tree);
	parser_destroy(&p);
	lexer_destroy(&l);

	// previous path
	ast = NULL;
	tree = NULL;
	pth = NULL;
	prog = NULL;

	char *str1 = "                                   ..       ;";
	l = Lexer_init(str1);
	p = Parser_init(&l);

	tree = Parse(&p);
	CU_ASSERT(tree != NULL);
	CU_ASSERT(ast_is_type(tree, AST_PROGRAM_TYPE));
	prog = (Program_Ast *)tree;

	CU_ASSERT(prog->commands.size == 1u);
	ast = list_get_nth(&prog->commands, 0u);
	CU_ASSERT(ast != NULL);
	CU_ASSERT(ast_is_type(ast, AST_PATH_TYPE));

	pth = (Path_Ast *)ast;
	CU_ASSERT(pth->args.size == 0u);
	CU_ASSERT(strcmp(string_get_c_string(pth->value), "..") == 0);

	ast_destroy(tree);
	parser_destroy(&p);
	lexer_destroy(&l);
}

void test_parser_single_path_as_argument_parse()
{
	char *str = "     cat         ../kjfg/gfg345/fgdf454 ; ";
	Ast *tree = NULL;
	Ast *ast = NULL;
	Program_Ast *prog = NULL;
	Command_Ast *comm = NULL;
	Path_Ast *pth = NULL;

	Lexer l = Lexer_init(str);
	Parser p = Parser_init(&l);

	CU_ASSERT(p.err == 0u);

	tree = Parse(&p);
	CU_ASSERT(tree != NULL);
	CU_ASSERT(ast_is_type(tree, AST_PROGRAM_TYPE));

	prog = (Program_Ast *)tree;

	CU_ASSERT(prog->commands.size == 1u);

	ast = (Ast *)list_get_nth(&prog->commands, 0u);

	CU_ASSERT(ast_is_type(ast, AST_COMMAND_TYPE));
	comm = (Command_Ast *)ast;

	CU_ASSERT(comm->args.size == 1u);
	CU_ASSERT(strcmp(string_get_c_string(comm->value), "cat") == 0);

	ast = list_get_nth(&comm->args, 0u);
	CU_ASSERT(ast != NULL);

	CU_ASSERT(ast_is_type(ast, AST_PATH_TYPE));
	pth = (Path_Ast *)ast;

	CU_ASSERT(strcmp(string_get_c_string(pth->value),
			 "../kjfg/gfg345/fgdf454") == 0);

	ast_destroy(tree);
	parser_destroy(&p);
	lexer_destroy(&l);
}
