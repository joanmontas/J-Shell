// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#include "Token.h"
#include <string.h>

const char *TOKEN_SYMBOL_TYPE = "symbol";
const char *TOKEN_IDENT_TYPE = "ident";
const char *TOKEN_QUOTED_TYPE = "quoted";
const char *TOKEN_EOF_TYPE = "eof";
const char *TOKEN_NONE_TYPE = "none";
const char *TOKEN_LEXER_ERROR_TYPE = "lexer_error";
const char *TOKEN_UNKOWN_ERROR_TYPE = "unkown_type";
// NOTE(Joan) Add as neeeded - Joan
const char *TOKEN_DELIMITERS = "<>|&*;\"";

void token_set_from_char_array(Token *t, const char *tkn_type,
			       const char *tkn_lit)
{
	if (t == NULL) {
		fprintf(stderr,
			"ERROR: token_set_from_char_array error. Given NULL instead of Token*\n");
		return;
	}

	t->token_type = string_init_c_string(tkn_type);
	t->literal = string_init_c_string(tkn_lit);
}

void token_set_from_char_array_and_string(Token *t, const char *tkn_type,
					  String *tkn_lit)
{
	if (t == NULL) {
		fprintf(stderr,
			"ERROR: token_set_from_char_array error. Given NULL instead of Token*\n");
		return;
	}

	t->token_type = string_init_c_string(tkn_type);
	t->literal = tkn_lit;
}

void token_reset(Token *t)
{
	if (t == NULL) {
		fprintf(stderr,
			"ERROR: token_reset error. Given NULL instead of Token*\n");
		return;
	}

	if (t->token_type != NULL) {
		string_destroy(t->token_type);
	}

	if (t->literal != NULL) {
		string_destroy(t->literal);
	}

	t->token_type = NULL;
	t->literal = NULL;
}

// TODO(Joan)
int token_is_type(Token *t, const char *tkn_type)
{
	if (t == NULL) {
		fprintf(stderr,
			"ERROR: token_get_type error. Given NULL instead of Token*\n");
		return -1;
	}

	if (t->token_type == NULL) {
		fprintf(stderr,
			"ERROR: token_get_type error. Token's token_type NULL instead of String*\n");
		return -1;
	}

	if (t->token_type->c_string == NULL) {
		fprintf(stderr,
			"ERROR: token_get_type error. Token's token_type's c_string NULL instead of char*\n");
		return -1;
	}

	if (strcmp(t->token_type->c_string, tkn_type) == 0) {
		return 1;
	}

	return 0;
}

const char *token_get_type(Token *t)
{
	if (t == NULL) {
		fprintf(stderr,
			"ERROR: token_get_type error. Given NULL instead of Token*\n");
		return TOKEN_LEXER_ERROR_TYPE;
	}

	if (t->token_type == NULL) {
		fprintf(stderr,
			"ERROR: token_get_type error. Token's token_type NULL instead of String*\n");
		return TOKEN_LEXER_ERROR_TYPE;
	}

	if (t->token_type->c_string == NULL) {
		fprintf(stderr,
			"ERROR: token_get_type error. Token's token_type's c_string NULL instead of char*\n");
		return TOKEN_LEXER_ERROR_TYPE;
	}

	// NOTE(Joan) Add as needed - Joan
	if (strcmp(t->token_type->c_string, TOKEN_SYMBOL_TYPE)) {
		return TOKEN_SYMBOL_TYPE;
	} else if (strcmp(t->token_type->c_string, TOKEN_IDENT_TYPE)) {
		return TOKEN_IDENT_TYPE;
	} else if (strcmp(t->token_type->c_string, TOKEN_EOF_TYPE)) {
		return TOKEN_EOF_TYPE;
	} else if (strcmp(t->token_type->c_string, TOKEN_NONE_TYPE)) {
		return TOKEN_NONE_TYPE;
	} else if (strcmp(t->token_type->c_string, TOKEN_LEXER_ERROR_TYPE)) {
		return TOKEN_LEXER_ERROR_TYPE;
	}

	return TOKEN_UNKOWN_ERROR_TYPE;
}

int is_delimeter(const char c)
{
	char c_prime = '\0';
	size_t i = 0u;
	size_t str_len = 0u;

	if (c == '\0') {
		return -1;
	}

	str_len = strlen(TOKEN_DELIMITERS);

	for (i = 0; i < str_len; i++) {
		c_prime = TOKEN_DELIMITERS[i];
		if (c == c_prime) {
			return 1;
		}
	}
	return 0;
}

char *token_get_c_string(Token *t)
{
	if (t == NULL) {
		fprintf(stderr,
			"ERROR: token_get_c_string error. Given NULL instead of Token*\n");
		return NULL;
	}

	return string_get_c_string(t->literal);
}