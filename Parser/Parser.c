// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#include "Parser.h"

Parser Parser_init(Lexer *l)
{
	Parser p;
	p.lex = l;

	p.err = 0;

	if (l == NULL) {
		fprintf(stderr, "ERROR: Parse_init. Given lexer in NULL\n");
		return p;
	}

	if (l->err) {
		p.err = 1;
	}

	p.errors = List_init();

	parser_next_token(&p);
	parser_next_token(&p);

	return p;
}

void parser_destroy(Parser *p)
{
	if (p == NULL) {
		fprintf(stderr, "ERROR: Parse destroy. Given parser in NULL\n");
		return;
	}

	list_destroy(&p->errors);

	p->err = 0;
}

Ast *Parse(Parser *p)
{
	Program_Ast *prog = NULL;
	Ast *ast = NULL;

	prog = (Program_Ast *)Ast_init_factory(AST_PROGRAM_TYPE, NULL);

	if (prog == NULL) {
		fprintf(stderr,
			"ERROR: Parse Error. Could not allocate enough memory for program\n");
		return NULL;
	}

	while (1) {
		if (token_is_type(p->current_token, TOKEN_EOF_TYPE)) {
			return (Ast *)prog;
		}

		if (token_is_type(p->current_token, TOKEN_LEXER_ERROR_TYPE)) {
			p->err++;
			fprintf(stderr,
				"ERROR: Parse Error. Lexical Error encountered\n");
			ast_destroy((Ast *)prog);
			return NULL;
		}

		ast = _parse(p);
		if (ast == NULL) {
			ast_destroy((Ast *)prog);
			fprintf(stderr,
				"ERROR: Parse Error. Gramatical Error encountered\n");
			return NULL;
		}
		list_append(&prog->commands, ast);
		parser_next_token(p);
	}
	return (Ast *)prog;
}

Ast *_parse(Parser *p)
{
	Command_Ast *comm = NULL;
	Path_Ast *pth = NULL;
	Ast *ast = NULL;

	if (p == NULL) {
		fprintf(stderr, "ERROR: _parse Error. Given parser is NULL\n");
		return NULL;
	}

	if (token_is_type(p->current_token, TOKEN_IDENT_TYPE)) {
		comm = (Command_Ast *)Ast_init_factory(
			AST_COMMAND_TYPE, token_get_c_string(p->current_token));

		if (comm == NULL) {
			fprintf(stderr,
				"ERROR: _parse Error. Could not allocate enough memory for Command\n");
			return NULL;
		}
		parser_next_token(p);

		while (1) {
			if (token_is_type(p->current_token, TOKEN_EOF_TYPE)) {
				ast_destroy((Ast *)comm);
				fprintf(stderr,
					"ERROR: _parse Error. Command Not terminated with semicolon\n");
				return NULL;
			}

			if (token_is_type(p->current_token,
					  TOKEN_SYMBOL_TYPE)) {
				if (strcmp(token_get_c_string(p->current_token),
					   ";") == 0) {
					return (Ast *)comm;

				} else {
					ast = parse_binary(p, (Ast *)comm);
					if (ast == NULL) {
						fprintf(stderr,
							"ERROR: _parse Error. Error while parsing binary Command\n");
						ast_destroy((Ast *)comm);
						return NULL;
					}
					return ast;
				}
			}

			ast = parse_token_to_ast_terminal(p->current_token);
			if (ast == NULL) {
				fprintf(stderr,
					"ERROR: _parse Error. Error while parsing terminal node in Command\n");
				ast_destroy((Ast *)comm);
				return NULL;
			}
			list_append(&comm->args, ast);
			parser_next_token(p);
		}

	} else if (token_is_type(p->current_token, TOKEN_PATH_TYPE)) {
		pth = (Path_Ast *)Ast_init_factory(
			AST_PATH_TYPE, token_get_c_string(p->current_token));

		if (pth == NULL) {
			fprintf(stderr,
				"ERROR: _parse Error. Could not allocate enough memory for Path\n");
			return NULL;
		}
		parser_next_token(p);

		while (1) {
			if (token_is_type(p->current_token, TOKEN_EOF_TYPE)) {
				ast_destroy((Ast *)pth);
				fprintf(stderr,
					"ERROR: _parse Error. Path Not terminated with semicolon\n");
				return NULL;
			}

			if (token_is_type(p->current_token,
					  TOKEN_SYMBOL_TYPE)) {
				if (strcmp(token_get_c_string(p->current_token),
					   ";") == 0) {
					return (Ast *)pth;

				} else {
					ast = parse_binary(p, (Ast *)pth);
					if (ast == NULL) {
						fprintf(stderr,
							"ERROR: _parse Error. Error while parsing binary Path\n");
						ast_destroy((Ast *)pth);
						return NULL;
					}
					return ast;
				}
			}

			ast = parse_token_to_ast_terminal(p->current_token);
			if (ast == NULL) {
				fprintf(stderr,
					"ERROR: _parse Error. Error while parsing terminal node in Path\n");
				ast_destroy((Ast *)pth);
				return NULL;
			}
			list_append(&pth->args, ast);
			parser_next_token(p);
		}
	} else {
		fprintf(stderr,
			"ERROR: _parse Error. Grammatically Incorrect. Expected starting with Command or Path\n");
		return NULL;
	}

	return NULL;
}

void parser_next_token(Parser *p)
{
	lexer_next_token((p->lex));
	p->current_token = &p->lex->current_token;
	p->peek_token = &p->lex->peek_token;
}

Ast *parse_token_to_ast_terminal(Token *t)
{
	Ast *ast = NULL;

	if (t == NULL) {
		fprintf(stderr,
			"ERROR: parse_token_to_ast Error. Given Token is NULL\n");
		return NULL;
	}

	if (token_is_type(t, TOKEN_IDENT_TYPE)) {
		ast = (Ast *)Ast_init_factory(AST_IDENT_TYPE,
					      token_get_c_string(t));

	} else if (token_is_type(t, TOKEN_QUOTED_TYPE)) {
		ast = (Ast *)Ast_init_factory(TOKEN_QUOTED_TYPE,
					      token_get_c_string(t));

	} else if (token_is_type(t, TOKEN_PATH_TYPE)) {
		ast = (Ast *)Ast_init_factory(TOKEN_PATH_TYPE,
					      token_get_c_string(t));

	} else {
		fprintf(stderr,
			"ERROR: parse_token_to_ast Error. Unkown Token\n");
		return NULL;
	}

	return ast;
}

Ast *parse_binary(Parser *p, Ast *left)
{
	Binary_Ast *bin = NULL;
	Ast *right = NULL;

	if (p == NULL) {
		fprintf(stderr,
			"ERROR: parse_binary Error. Given parser is NULL\n");
		return NULL;
	}

	if (left == NULL) {
		fprintf(stderr,
			"ERROR: parse_binary Error. Given left tree is NULL\n");
		return NULL;
	}

	bin = (Binary_Ast *)Ast_init_factory(
		AST_SYMBOL_TYPE, token_get_c_string(p->current_token));

	if (bin == NULL) {
		fprintf(stderr,
			"ERROR: parse_binary Error. Could not allocate enough memory for binary ast\n");
		return NULL;
	}

	parser_next_token(p);

	right = _parse(p);

	if (right == NULL) {
		fprintf(stderr,
			"ERROR: parse_binary Error. Error while parsing right side of tree\n");
		ast_destroy((Ast *)bin);
		return NULL;
	}

	bin->left = left;
	bin->right = right;

	return (Ast *)bin;
}