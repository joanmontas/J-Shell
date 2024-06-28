// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#ifndef EVALUATOR_H
#define EVALUATOR_H
#include "../Ast/Ast.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1

extern const char *EVALUATOR_PATH;

typedef struct Cmd_Args_format {
	char *cmd;
	char **args;
	size_t size;
} Cmd_Args_format;

// evaluation
int Evaluate(Program_Ast *p, int original_fd[2]);
int eval(Ast *ast, int input_fd, int output_fd);
int exec_command(const char *cmd, char **arg, int input_fd, int output_fd);
// helper
Cmd_Args_format *cmd_and_arg_formater(Ast *ast);
void cmd_args_destroy(Cmd_Args_format *caf);

#endif // EVALUATOR_H