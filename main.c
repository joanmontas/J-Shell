// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
	char *buffer = NULL;
	size_t buffer_size = 0;
	ssize_t char_read;

	while (1) {
		printf("<user_name>@<computer_name>: ");

		char_read = getline(&buffer, &buffer_size, stdin);

		if (char_read == -1) {
			fprintf(stderr,
				"ERROR: REPL error. Unable to get line\n");
			break;
		}

		if (strcmp(buffer, "exit\n") == 0) {
			free(buffer);
			buffer = NULL;
			break;
		}

		printf("%s", buffer);

		free(buffer);
		buffer = NULL;
	}

	return 0;
}

