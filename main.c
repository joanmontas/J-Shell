// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#include <unistd.h>

#include "./Lexer/Lexer.h"
#include "./Ast/Ast.h"
#include "./Parser/Parser.h"
#include "Evaluator/Evaluator.h"

int main()
{
	char *buffer = NULL;
	size_t buffer_size = 0;
	ssize_t char_read;

	int rslt = 0;
	Lexer l;
	Parser p;
	Ast *tree = NULL;

	while (1) {
		printf("<user_name>@<computer_name>: ");

		char_read = getline(&buffer, &buffer_size, stdin);

		if (char_read == -1) {
			printf("ERROR: REPL error. Unable to get line\n");
			break;
		}

		if (buffer[char_read - 1] == '\n') {
			buffer[char_read - 1] = '\0';
		}

                // build in
		if ((strcmp(buffer, "exit\n") == 0)) {
			free(buffer);
			buffer = NULL;
			break;
		}

		l = Lexer_init(buffer);
		p = Parser_init(&l);

		tree = Parse(&p);
		if (tree == NULL) {
			printf("Error occured while parsing\n");

		} else {
			rslt = Evaluate((Program_Ast *)tree);
			if (rslt == -1) {
				printf("Error occured while evaluating\n");
			}
			ast_destroy(tree);
		}

		parser_destroy(&p);
		lexer_destroy(&l);
		free(buffer);
		buffer = NULL;
	}

	return 0;
}
