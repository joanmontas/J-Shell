// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#ifndef AST_H
#define AST_H

#include <string.h>
#include "../String/String.h"
#include "../List/List.h"

extern const char *AST_PROGRAM_TYPE;
extern const char *AST_COMMAND_TYPE;
extern const char *AST_BINARY_TYPE;
extern const char *AST_IDENT_TYPE;
extern const char *AST_QUOTED_TYPE;
extern const char *AST_PATH_TYPE;

typedef struct Ast {
	const char *ast_type;
} Ast;

typedef struct Program_Ast {
	Ast ast;
	List commands;
} Program_Ast;

typedef struct Command_Ast {
	Ast ast;
	String *value;
	List args;
} Command_Ast;

typedef struct Binary_ast {
	Ast ast;
	String *value;
	Ast *left;
	Ast *right;
} Binary_ast;

typedef struct Ident_Ast {
	Ast ast;
	String *value;
} Ident_Ast;

typedef struct Quoted_Ast {
	Ast ast;
	String *value;
} Quoted_Ast;

typedef struct Path_Ast {
	Ast ast;
	String *value;
	List args;
} Path_Ast;

typedef struct _Type_and_Value_Ast {
	Ast ast;
	String *value;
} _Type_and_Value_Ast;

Ast *Ast_init_factory(const char *type, char *val);
void ast_destroy(Ast *ast);
int ast_is_type(Ast *ast, const char *ast_type);
char *ast_get_value(Ast *ast);
size_t ast_get_value_size(Ast *ast);

#endif // AST_H