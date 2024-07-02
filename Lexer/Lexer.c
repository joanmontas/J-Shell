// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#include "Lexer.h"

Lexer Lexer_init(char *input_str)
{
	// ZERO element initialized
	Lexer lex;
	lex.input_string = input_str;
	lex.input_size = 0u;
	lex.position = 0u;
	lex.current_char = '\0';
	lex.err = 0;

	token_set_from_char_array(&(lex.current_token), TOKEN_NONE_TYPE,
				  TOKEN_NONE_TYPE);
	token_set_from_char_array(&(lex.peek_token), TOKEN_NONE_TYPE,
				  TOKEN_NONE_TYPE);

	if (input_str == NULL) {
		fprintf(stderr,
			"ERROR: Lexer_init error. Given NULL instead of char*\n");
		token_reset(&(lex.current_token));
		token_reset(&(lex.peek_token));
		token_set_from_char_array(&(lex.current_token),
					  TOKEN_LEXER_ERROR_TYPE,
					  TOKEN_LEXER_ERROR_TYPE);
		token_set_from_char_array(&(lex.peek_token),
					  TOKEN_LEXER_ERROR_TYPE,
					  TOKEN_LEXER_ERROR_TYPE);
		lex.err = 1;
		return lex;
	};

	lex.input_string = input_str;
	lex.input_size = strlen(input_str);

	if (lex.input_size == 0) {
		lex.current_char = '\0';
	} else {
		lex.current_char = lex.input_string[0];
	}

	return lex;
}

// TODO(Joan) lex for path start with . or / and ends in white space
size_t lexer_next_token(Lexer *lex)
{
	char c = '\0';
	String *s = string_init_default();

	if (lex == NULL) {
		fprintf(stderr,
			"ERROR: Lexer_next_token error. Given NULL instead of Lexer\n");
		string_destroy(s);
		return 0u;
	}

	if (strcmp(lex->current_token.token_type->c_string,
		   TOKEN_LEXER_ERROR_TYPE) == 0) {
		fprintf(stderr,
			"ERROR: Lexer_next_token error. Current token contains a lexical error\n");
		string_destroy(s);
		return 0u;
	}

	if (strcmp(lex->current_token.token_type->c_string, TOKEN_EOF_TYPE) ==
	    0) {
		fprintf(stderr,
			"ERROR: Lexer_next_token error. Current token is end of file\n");
		string_destroy(s);
		return 1u;
	}

	if (strcmp(lex->peek_token.token_type->c_string, TOKEN_EOF_TYPE) == 0) {
		string_destroy(s);
		token_reset(&(lex->current_token));
		token_set_from_char_array(&(lex->current_token), TOKEN_EOF_TYPE,
					  TOKEN_EOF_TYPE);
		return 0u;
	}

	if (strcmp(lex->peek_token.token_type->c_string,
		   TOKEN_LEXER_ERROR_TYPE) == 0) {
		fprintf(stderr,
			"ERROR: Lexer_next_token error. Current token is end of file\n");
		string_destroy(s);
		token_reset(&(lex->current_token));
		token_set_from_char_array(&(lex->current_token),
					  TOKEN_LEXER_ERROR_TYPE,
					  TOKEN_LEXER_ERROR_TYPE);
		return 0u;
	}

	// peek_token becomes new
	token_reset(&(lex->current_token));
	lex->current_token = lex->peek_token;

	lexer_eat_white_space(lex);

	c = lex->current_char;

	if (c == '\0') {
		token_set_from_char_array(&(lex->peek_token), TOKEN_EOF_TYPE,
					  TOKEN_EOF_TYPE);
		string_destroy(s);
		return 1u;
	} else if (c == '"') {
		lexer_next_character(lex);
		c = lex->current_char;
		while (1) {
			if (c == '"') {
				token_set_from_char_array_and_string(
					&(lex->peek_token), TOKEN_QUOTED_TYPE,
					s);
				lexer_next_character(lex);
				return 1u;

			} else if (c == '\0') {
				fprintf(stderr,
					"ERROR: Lexer_next_token error. Quote not terminated\n");
				token_set_from_char_array(
					&(lex->peek_token),
					TOKEN_LEXER_ERROR_TYPE,
					TOKEN_LEXER_ERROR_TYPE);
				lexer_next_character(lex);
				string_destroy(s);
				lex->err = 1;
				return 0u;
			}
			string_append_char(s, c);
			lexer_next_character(lex);
			c = lex->current_char;
		}
	} else if (c == '.' || c == '/') {
		while (1) {
			if (c == '\0' || c == ' ' || is_delimeter(c)) {
				token_set_from_char_array_and_string(
					&(lex->peek_token), TOKEN_PATH_TYPE, s);
				return 1u;
			}
			string_append_char(s, c);
			lexer_next_character(lex);
			c = lex->current_char;
		}
	} else if (is_delimeter(c)) {
		string_append_char(s, c);
		char cc = lexer_peek_next_character(lex);
		if (c == '>' && cc == '>') {
			lexer_next_character(lex);
			string_append_char(s, cc);
		}
		token_set_from_char_array_and_string(&(lex->peek_token),
						     TOKEN_SYMBOL_TYPE, s);
		lexer_next_character(lex);
		return 1u;

	} else {
		while (1) {
			if (c == '\0' || c == ' ' || is_delimeter(c)) {
				token_set_from_char_array_and_string(
					&(lex->peek_token), TOKEN_IDENT_TYPE,
					s);
				return 1u;
			}
			string_append_char(s, c);
			lexer_next_character(lex);
			c = lex->current_char;
		}
	}
	string_destroy(s);
	return 1u;
}

void lexer_next_character(Lexer *lex)
{
	if (lex == NULL) {
		fprintf(stderr,
			"ERROR: Lexer_next_character error. Given NULL instead of Lexer\n");
		return;
	}
	lex->position++;
	if (lex->position >= lex->input_size) {
		lex->position--;
		lex->current_char = '\0';
		return;
	}
	lex->current_char = lex->input_string[lex->position];
}

void lexer_eat_white_space(Lexer *lex)
{
	// eats all whites space and new line character
	char c = '\0';
	if (lex == NULL) {
		fprintf(stderr,
			"ERROR: Lexer_eat_white_space error. Given NULL instead of Lexer\n");
		return;
	}

	while (1) {
		c = lex->current_char;
		if (c == ' ' || c == '\n' || c == '\t') {
			lexer_next_character(lex);
		} else {
			return;
		}
	}
}

void lexer_destroy(Lexer *l)
{
	if (l == NULL) {
		fprintf(stderr,
			"ERROR: lexer_destroy error. Received NULL instead of Lexer*\n");
		return;
	};
	token_reset(&(l->current_token));
	token_reset(&(l->peek_token));
}

char lexer_peek_next_character(Lexer *lex)
{
	if (lex == NULL) {
		fprintf(stderr,
			"ERROR: lexer_peek_next_character error. Received NULL instead of Lexer*\n");
		return '\0';
	};

	if (lex->position + 1u > lex->input_size) {
		fprintf(stderr,
			"ERROR: lexer_peek_next_character error. Peek char out of range\n");

		return '\0';
	}

	return lex->input_string[lex->position + 1u];
}