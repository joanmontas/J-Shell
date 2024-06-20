// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "../String/String.h"

extern const char *TOKEN_SYMBOL_TYPE;
extern const char *TOKEN_IDENT_TYPE;
extern const char *TOKEN_QUOTED_TYPE;
extern const char *TOKEN_EOF_TYPE;
extern const char *TOKEN_NONE_TYPE;
extern const char *TOKEN_LEXER_ERROR_TYPE;
extern const char *TOKEN_UNKOWN_ERROR_TYPE;
extern const char *TOKEN_DELIMITERS;

typedef struct Token {
	String *token_type;
	String *literal;
} Token;

void token_set(Token *t, char *tkn_type, char *tkn_lit);
void token_reset(Token *t);
void token_set_from_char_array(Token *t, const char *tkn_type,
			       const char *tkn_lit);
void token_set_from_char_array_and_string(Token *t, const char *tkn_type,
					  String *tkn_lit);

// TODO(Joan) Make sure to test this helper functions - Joan
int token_is_type(Token *t, const char *tkn_type);
const char *token_get_type(Token *t);
int is_delimeter(const char c);
char *token_get_c_string(Token *t);

#endif // TOKEN_H
