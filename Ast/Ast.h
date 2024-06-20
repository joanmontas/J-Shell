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
extern const char *AST_SYMBOL_TYPE;
extern const char *AST_IDENT_TYPE;
extern const char *AST_QUOTED_TYPE;

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

typedef struct Binary_Ast {
	Ast ast;
	String *value;
	Ast *left;
	Ast *right;
} Binary_Ast;

typedef struct Ident_Ast {
	Ast ast;
	String *value;
} Ident_Ast;

typedef struct Quoted_Ast {
	Ast ast;
	String *value;
} Quoted_Ast;

Ast *Ast_init_factory(const char *type, char *val);
void ast_destroy(Ast *ast);
int ast_is_type(Ast *ast, const char *ast_type);
#endif // AST_H