// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#include <unistd.h>
#include <limits.h>

#include "./Lexer/Lexer.h"
#include "./Ast/Ast.h"
#include "./Parser/Parser.h"
#include "./utils/Return_Codes/Return_codes.h"
#include "Evaluator/Evaluator.h"

// void handle_signal(int sig)
// {
// 	printf("Exiting...\n");
// }

int main()
{
	/*if (signal(SIGINT, handle_signal) == SIG_ERR) {
		return 1;
	}*/

	char hostname[HOST_NAME_MAX + 1];
	char current_working_directory[PATH_MAX + 1];

	char *username;

	char *buffer = NULL;
	size_t buffer_size = 0;
	ssize_t char_read;

	int rslt = 0;
	Lexer l;
	Parser p;
	Ast *tree = NULL;

	if (gethostname(hostname, HOST_NAME_MAX + 1) != 0) {
		printf("Error: REPL error. Unable to get hostname\n");
		return 1;
	}
	hostname[HOST_NAME_MAX] = '\0';

	if (getcwd(current_working_directory, PATH_MAX) == NULL) {
		printf("Error: REPL error. Unable to get working directory\n");
		return 1;
	}
	current_working_directory[PATH_MAX] = '\0';

	while (1) {
		username = NULL;

		username = getlogin();

		printf("[%s@%s]-[%s]: ", username, hostname,
		       current_working_directory);

		char_read = getline(&buffer, &buffer_size, stdin);

		if (char_read == -1) {
			printf("ERROR: REPL error. Unable to get line\n");
			break;
		}

		if (char_read > 0 && buffer[char_read - 1] == '\n') {
			buffer[char_read - 1] = '\0';
		}

		// build in
		if ((strcmp(buffer, "exit") == 0)) {
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
				ast_destroy(tree);
				parser_destroy(&p);
				lexer_destroy(&l);
				free(buffer);
				buffer = NULL;
				return 0;
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
