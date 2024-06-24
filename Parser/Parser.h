// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#ifndef PARSER_H
#define PARSER_H

#include "../Token/Token.h"
#include "../Ast/Ast.h"
#include "../String/String.h"
#include "../List/List.h"
#include "../Lexer/Lexer.h"

typedef struct Parser {
	Lexer *lex;
	Token *current_token;
	Token *peek_token;
	List errors;
	size_t err;
} Parser;

// // constructor and destructor
Parser Parser_init(Lexer *l);
void parser_destroy(Parser *p);
// parse
Ast *Parse(Parser *p);
Ast *_parse(Parser *p);
// helper
void parser_next_token(Parser *p);
Ast *parse_token_to_ast_terminal(Token *t);
Ast *parse_binary(Parser *p, Ast *left);
#endif // PARSER_H