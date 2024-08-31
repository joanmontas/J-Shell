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

/**
 * @brief A struct to store parsing states.
 *
 * @fields:
 *     - lex: Struct storing lexer states.
 *     - curent_token: Points to the current struct to be analyze.
 *     - peek_token: Points to the next struct to be analyze.
 *     - errors: List
 *     - err: The person's age.
 */

typedef struct Parser {
	Lexer *lex;
	Token *current_token;
	Token *peek_token;
	List errors;
	size_t err;
} Parser;

// constructor | destructor //

/**
 * Initializes parameters of Parser given a valid Lexer.
 *
 * @param l Address to Lexer
 * @return Initialized Parser
 */
Parser Parser_init(Lexer *l);

/**
 * Destroy Parser's inner fields.
 *
 * @param p Address to Parser
 * @return void
 */
void parser_destroy(Parser *p);

// parse //

/**
 * Destroy Parser's inner fields.
 *
 * @param p Address to Parser
 * @return The abstract syntax tree, single parse.
 */
Ast *Parse(Parser *p);
Ast *_parse(Parser *p);

// helper
void parser_next_token(Parser *p);
Ast *parse_token_to_ast_terminal(Token *t);
Ast *parse_binary(Parser *p, Ast *left);
#endif // PARSER_H