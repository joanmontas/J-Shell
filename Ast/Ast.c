// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#include "Ast.h"

const char *AST_PROGRAM_TYPE = "program";
const char *AST_COMMAND_TYPE = "command";
const char *AST_SYMBOL_TYPE = "symbol";
const char *AST_IDENT_TYPE = "ident";
const char *AST_QUOTED_TYPE = "quoted";

Ast *Ast_init_factory(const char *type, char *val)
{
	Ast *ptr = NULL;

	if (type == NULL) {
		return NULL;
	}

	if (strcmp(type, AST_PROGRAM_TYPE) == 0) {
		ptr = (Ast *)malloc(sizeof(Program_Ast));
		((Program_Ast *)ptr)->commands = List_init();
		ptr->ast_type = type;
		return ptr;
	}

	if (val == NULL) {
		return NULL;
	}

	if (strcmp(type, AST_COMMAND_TYPE)) {
		ptr = (Ast *)malloc(sizeof(Command_Ast));
		((Command_Ast *)ptr)->value = string_init_c_string(val);
	} else if (strcmp(type, AST_SYMBOL_TYPE)) {
		ptr = (Ast *)malloc(sizeof(Binary_Ast));
		((Binary_Ast *)ptr)->value = string_init_c_string(val);
		((Binary_Ast *)ptr)->left = NULL;
		((Binary_Ast *)ptr)->right = NULL;
	} else if (strcmp(type, AST_IDENT_TYPE)) {
		ptr = (Ast *)malloc(sizeof(Ident_Ast));
		((Ident_Ast *)ptr)->value = string_init_c_string(val);
	} else if (strcmp(type, AST_QUOTED_TYPE)) {
		ptr = (Ast *)malloc(sizeof(Quoted_Ast));
		((Quoted_Ast *)ptr)->value = string_init_c_string(val);
	} else {
		return NULL;
	}

	ptr->ast_type = type;
	return ptr;
}

void ast_destroy(Ast *ast)
{
	Program_Ast *prog = NULL;
	Command_Ast *comm = NULL;
	Binary_Ast *bin = NULL;
	Ident_Ast *id = NULL;
	Quoted_Ast *qted = NULL;
	size_t i = 0u;
	Ast *tmp = NULL;

	if (strcmp(ast->ast_type, AST_PROGRAM_TYPE) == 0) {
		prog = (Program_Ast *)ast;
		for (i = 0u; i < prog->commands.size; i++) {
			tmp = (Ast *)list_get_nth(&prog->commands, i);
			ast_destroy(tmp);
		}
		list_destroy(&(prog->commands));
	} else if (strcmp(ast->ast_type, AST_COMMAND_TYPE)) {
		comm = (Command_Ast *)ast;
		string_destroy(comm->value);
	} else if (strcmp(ast->ast_type, AST_SYMBOL_TYPE)) {
		bin = (Binary_Ast *)ast;
		string_destroy(bin->value);
	} else if (strcmp(ast->ast_type, AST_IDENT_TYPE)) {
		id = (Ident_Ast *)ast;
		string_destroy(id->value);
	} else if (strcmp(ast->ast_type, AST_QUOTED_TYPE)) {
		qted = (Quoted_Ast *)ast;
		string_destroy(qted->value);
	} else {
		return;
	}

	free(ast);
}
