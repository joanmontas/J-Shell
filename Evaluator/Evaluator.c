// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#include "Evaluator.h"
#include <stdio.h>

const char *EVALUATOR_PATH = "/bin/";

int Evaluate(Program_Ast *p, int original_fd[2])
{
	int rslt = 0;
	Ast *ast = NULL;
	size_t i = 0u;

	if (p == NULL) {
		fprintf(stderr, "ERROR: Evaluate. Given Ast in NULL\n");
		return -1;
	}

	for (i = 0u; i < p->commands.size; i++) {
		ast = list_get_nth(&p->commands, i);

		rslt = eval(ast, original_fd[READ_END], original_fd[WRITE_END]);

		if (rslt == -1) {
			fprintf(stderr,
				"ERROR: Evaluate. Error while evaluating\n");
			return rslt;
		}
	}

	return 0;
}

int eval(Ast *ast, int input_fd, int output_fd)
{
	int rslt = 0;

	if (ast == NULL) {
		fprintf(stderr, "ERROR: eval. Given Ast in NULL\n");
		return -1;
	}

	if (ast_is_type(ast, AST_COMMAND_TYPE)) {
		Cmd_Args_format *caf = cmd_and_arg_formater(ast);
		if (caf == NULL) {
			fprintf(stderr,
				"ERROR: eval. Error while formating commands and argument");
			return -1;
		}

		rslt = exec_command(caf->cmd, caf->args, input_fd, output_fd);

		cmd_args_destroy(caf);

		if (rslt != 1) {
			return rslt;
		}

		return 1;

	} else if (ast_is_type(ast, AST_PATH_TYPE)) {
		Cmd_Args_format *caf = cmd_and_arg_formater(ast);
		if (caf == NULL) {
			fprintf(stderr,
				"ERROR: eval. Error while formating commands and argument");
			return -1;
		}

		rslt = exec_command(caf->cmd, caf->args, input_fd, output_fd);

		cmd_args_destroy(caf);

		if (rslt != 1) {
			return rslt;
		}

		return 1;

	} else if (ast_is_type(ast, AST_BINARY_TYPE)) {
		printf("TODO(Joan) finish settings this up\n");
		printf("Piped command\n");

		Binary_ast *smb = (Binary_ast *)ast;
		int intermediary_fd[2];

		Ast *l = smb->left;
		Ast *r = smb->right;

		if (strcmp(smb->value->c_string, "|") == 0) {
			if (pipe(intermediary_fd) == -1) {
				fprintf(stderr,
					"ERROR: while creating intermediary pipe");
				return -1;
			}

			rslt = eval(l, input_fd, intermediary_fd[WRITE_END]);
			close(intermediary_fd[WRITE_END]);

			if (rslt == -1) {
				close(intermediary_fd[READ_END]);
				return -1;
			}

			rslt = eval(r, intermediary_fd[READ_END], output_fd);
			close(intermediary_fd[READ_END]);

			return rslt;

		} else {
			// NOTE(Joan) Add more binary symbol as needed
			fprintf(stderr,
				"ERROR: eval was unable to recognized binary symbol");
		}

		return -1;

	} else {
		fprintf(stderr, "ERROR: eval. Error while executing command");
		return -1;
	}

	return -1;
}

int exec_command(const char *cmd, char **arg, int input_fd, int output_fd)
{
	pid_t pid = fork();

	if (pid < 0) {
		fprintf(stderr, "ERROR: exec_command error. Unable to fork");
		return -1;
	}

	if (pid == 0) {
		// Child process

		if (input_fd != 0) {
			dup2(input_fd, 0);
			close(input_fd);
		}

		if (output_fd != 1) {
			dup2(output_fd, 1);
			close(output_fd);
		}

		execve(cmd, arg, NULL);
		fprintf(stderr,
			"Error: exec_command error. Unable to execute execve");
		return -1;
	} else {
		// Parent process

		waitpid(pid, NULL, 0);
	}

	return 0;
}

Cmd_Args_format *cmd_and_arg_formater(Ast *ast)
{
	int rslt = 0;
	Cmd_Args_format *caf = NULL;

	if (ast == NULL) {
		fprintf(stderr,
			"ERROR: cmd_and_arg_formater. Given Ast is NULL");
		return NULL;
	}

	// NOTE(Joan) The code is very WET, please DRY it - Joan

	if (ast_is_type(ast, AST_COMMAND_TYPE)) {
		Command_Ast *comm = (Command_Ast *)ast;

		String *str = string_init_c_string(EVALUATOR_PATH);

		if (str == NULL) {
			fprintf(stderr,
				"ERROR: cmd_and_arg_formater. Could not allocate memory for Cmd_Args_format");
			return NULL;
		}

		rslt = string_concat(str, comm->value);

		if (rslt != 1) {
			fprintf(stderr,
				"ERROR: cmd_and_arg_formater. Error while concatenating string");
			string_destroy(str);
			return NULL;
		}

		caf = (Cmd_Args_format *)malloc(sizeof(Cmd_Args_format));
		if (caf == NULL) {
			fprintf(stderr,
				"ERROR: cmd_and_arg_formater. Could not allocate memory for Cmd_Args_format");
			string_destroy(str);
			return NULL;
		}

		caf->size = comm->args.size + 2;

		caf->cmd = (char *)malloc((str->size + 1) * sizeof(char));
		if (caf->cmd == NULL) {
			fprintf(stderr,
				"ERROR: cmd_and_arg_formater. Could not allocate memory for Cmd_Args_format's cmd");
			string_destroy(str);
			free(caf);
			return NULL;
		}

		strcpy(caf->cmd, str->c_string);

		caf->args = (char **)malloc((caf->size) * sizeof(char *));
		if (caf->args == NULL) {
			fprintf(stderr,
				"ERROR: cmd_and_arg_formater. Could not allocate memory for Cmd_Args_format's args");
			string_destroy(str);
			free(caf->cmd);
			free(caf);
			return NULL;
		}
		caf->args[caf->size - 1u] = NULL;

		caf->args[0] = (char *)malloc((str->size + 1) * sizeof(char));
		if (caf->args[0] == NULL) {
			fprintf(stderr,
				"ERROR: cmd_and_arg_formater. Could not allocate memory for Cmd_Args_format's args [0]");
			string_destroy(str);
			free(caf->cmd);
			free(caf->args);
			free(caf);
			return NULL;
		}

		strcpy(caf->args[0], str->c_string);
		string_destroy(str);

		for (size_t i = 1u; i < comm->args.size + 1u; i++) {
			Ast *tmp_str = (Ast *)list_get_nth(&comm->args, i - 1);
			if (tmp_str == NULL) {
				for (size_t j = 0u; j < i; j++) {
					free(caf->args[j]);
				}
				free(caf->cmd);
				free(caf->args);
				free(caf);
				return NULL;
			}

			caf->args[i] = (char *)malloc(
				(ast_get_value_size(tmp_str) + 1) *
				sizeof(char));
			if (caf->args[i] == NULL) {
				for (size_t j = 0u; j < i; j++) {
					free(caf->args[j]);
				}
				free(caf->cmd);
				free(caf->args);
				free(caf);
				return NULL;
			}
			strcpy(caf->args[i], ast_get_value(tmp_str));
		}

		return caf;
	}

	if (ast_is_type(ast, AST_PATH_TYPE)) {
		Path_Ast *pth = (Path_Ast *)ast;

		caf = (Cmd_Args_format *)malloc(sizeof(Cmd_Args_format));
		if (caf == NULL) {
			fprintf(stderr,
				"ERROR: cmd_and_arg_formater. Could not allocate memory for Cmd_Args_format");
			return NULL;
		}
		caf->size = pth->args.size + 2;
		caf->cmd =
			(char *)malloc((pth->value->size + 1) * sizeof(char));

		if (caf->cmd == NULL) {
			fprintf(stderr,
				"ERROR: cmd_and_arg_formater. Could not allocate memory for Cmd_Args_format's cmd");
			free(caf);
			return NULL;
		}

		strcpy(caf->cmd, pth->value->c_string);

		caf->args = (char **)malloc((caf->size) * sizeof(char *));
		if (caf->args == NULL) {
			fprintf(stderr,
				"ERROR: cmd_and_arg_formater. Could not allocate memory for Cmd_Args_format's args");
			free(caf->cmd);
			free(caf);
			return NULL;
		}
		caf->args[caf->size - 1u] = NULL;

		caf->args[0] =
			(char *)malloc((pth->value->size + 1) * sizeof(char));
		if (caf->args[0] == NULL) {
			fprintf(stderr,
				"ERROR: cmd_and_arg_formater. Could not allocate memory for Cmd_Args_format's args [0]");
			free(caf->cmd);
			free(caf->args);
			free(caf);
			return NULL;
		}
		strcpy(caf->args[0], pth->value->c_string);

		for (size_t i = 1u; i < pth->args.size + 1u; i++) {
			Ast *tmp_str = (Ast *)list_get_nth(&pth->args, i - 1);
			if (tmp_str == NULL) {
				for (size_t j = 0u; j < i; j++) {
					free(caf->args[j]);
				}
				free(caf->cmd);
				free(caf->args);
				free(caf);
				return NULL;
			}

			caf->args[i] = (char *)malloc(
				(ast_get_value_size(tmp_str) + 1) *
				sizeof(char));
			if (caf->args[i] == NULL) {
				for (size_t j = 0u; j < i; j++) {
					free(caf->args[j]);
				}
				free(caf->cmd);
				free(caf->args);
				free(caf);
				return NULL;
			}
			strcpy(caf->args[i], ast_get_value(tmp_str));
		}

		return caf;
	}

	fprintf(stderr, "ERROR: cmd_and_arg_formater unkown type");
	return NULL;
}

void cmd_args_destroy(Cmd_Args_format *caf)
{
	if (caf == NULL) {
		fprintf(stderr, "ERROR: cmd_and_arg_destroy. Given NULL");
		return;
	}
	for (size_t i = 0u; i < caf->size; i++) {
		free(caf->args[i]);
	}
	free(caf->args);
	free(caf->cmd);
	free(caf);
}