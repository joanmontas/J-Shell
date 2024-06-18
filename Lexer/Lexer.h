// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../Token/Token.h"
#include "../String/String.h"

typedef struct Lexer {
	char *input_string;
	size_t input_size;
	size_t position;
	char current_char;
	Token current_token;
	Token peek_token;
	int err;
} Lexer;

// // constructor and destructor
Lexer Lexer_init(char *input_str);
void lexer_destroy(Lexer *l);
// // get token in sequence
size_t lexer_next_token(Lexer *lex);
// // helpers
void lexer_next_character(Lexer *lex);
void lexer_eat_white_space(Lexer *lex);

// char peekNextCharacter(Lexer *lex);
// // extracting IDENT and or keywords
// char *extractIDENT(Lexer *lex);
// char *extractINT(Lexer *lex);
// Token extractString(Lexer *lex);

#endif // LEXER_H