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

/**
 * @brief A struct that holds formated Ast as required by execution
 *
 * @fields:
 *     - cmd: The name-space to be executed
 *     - args: Null terminated array containing name-space and all args
 *     - size: Size of the 'args' field
 */

typedef struct Cmd_Args_format {
	char *cmd;
	char **args;
	size_t size;
} Cmd_Args_format;

// evaluation //

/**
 * Initializes parameters of Parser given a valid Lexer.
 *
 * @param p Program Ast containing List of command to be executed.
 *          Evaluation is outputed into current file descriptor
 * @return An int '-1' upon execution error
 */

int Evaluate(Program_Ast *p);
int eval_pipe(Ast *ast, int input_fd, int output_fd);
int eval_symbol_pipe(Ast *ast, int input_fd, int output_fd);
int exec_command_single(const char *cmd, char **arg);
int exec_command_pipe(const char *cmd, char **arg, int input_fd, int output_fd);

// helper
Cmd_Args_format *cmd_and_arg_formater(Ast *ast);
void cmd_args_destroy(Cmd_Args_format *caf);

#endif // EVALUATOR_H