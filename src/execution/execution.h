/*
** EPITECH PROJECT, 2024
** src/execution/execution.h
** File description:
** Defines builtins' prototypes
** Author: @lszsrd
*/

#pragma once

#include "shell.h"

/*
 * Macro: WRONG_ARCHITECTURE
 * -------------------------
 * Defines error message when the executed binary has a different architecture
 */
#define WRONG_ARCHITECTURE " Wrong Architecture."

/*
 * Prototypes definition
 */

void expand_ast(shell_t *shell, const ast_t *ast);
void execute_parentheses(shell_t *shell, const ast_t *ast);

/*
 * Operators handling's prototypes definition
 * ------------------------------------------
 */

void execute_operators(shell_t *shell, const ast_t *ast);

/*
 * Redirects handling's prototypes definition
 * ------------------------------------------
 */

void execute_redirects(shell_t *shell, const ast_t *ast);

int redirect_pipe(shell_t *shell, const ast_t *ast);
int redirect_input(shell_t *shell, const ast_t *ast);
int redirect_output(shell_t *shell, const ast_t *ast);
int redirect_append(shell_t *shell, const ast_t *ast);
int redirect_heredoc(shell_t *shell, const ast_t *ast);

/*
 * Command and builtin's handling prototypes definition
 * ----------------------------------------------------
 */

int check_command(shell_t *shell, ast_t *ast);
char *expand_globbins(const char *binary, const char *argument);

int execute_builtin(shell_t *shell, const ast_t *ast);
void execute_command(shell_t *shell, const ast_t *ast, int register_status);
