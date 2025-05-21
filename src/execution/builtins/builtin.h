/*
** EPITECH PROJECT, 2024
** src/execution/builtins/builtin.h
** File description:
** Defines shell's builtins prototypes
** Author: @lszsrd
*/

#pragma once

/*
 * Important note: this file should never be called "builtins.h" as a header
 *  file with the same name already exist somewhere, causing include issues
 */

/*
 * HOW-TO: Add a new builtin
 * -------------------------
 *  1. Add its executable name in the 'builtins_names' variable in
 *      'src/execution/commands/execute_builtin.c' file
 *  2. Create a new file and function in the 'src/execution/builtins' folder
 *  3. Add its prototype below with the same return type and arguments
 *  4. Add its function name to the 'builtins' array to functions pointers in
 *      'src/execution/commands/execute_builtin.c' file
 *  5. Make sure that builtin's name has the same index in the 'builtins'
 *      array to functions pointers
 *  6. Test out that the builtin doesn't cause issues on the shell and create
 *      unit tests
 */

#include "shell.h"

/*
 * Prototypes definition
 */

int b_exit(shell_t *shell, const char **argv);
int b_env(shell_t *shell, const char **argv);
int b_setenv(shell_t *shell, const char **argv);
int b_unsetenv(shell_t *shell, const char **argv);
int b_cd(shell_t *shell, const char **argv);
int b_set(shell_t *shell, const char **argv);
int b_unset(shell_t *shell, const char **argv);
int b_alias(shell_t *shell, const char **argv);
int b_unalias(shell_t *shell, const char **argv);
int b_history(shell_t *shell, const char **argv);
int b_printenv(shell_t *shell, const char **argv);
int b_builtins(shell_t *shell, const char **argv);
int b_echo(shell_t *shell, const char **argv);
int b_exclamation_mark(shell_t *shell, const char **argv);
