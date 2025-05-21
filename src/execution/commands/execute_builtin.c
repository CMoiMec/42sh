/*
** EPITECH PROJECT, 2024
** src/execution/commands/execute_builtin.c
** File description:
** Checks if given command is a builtin command, if so, executes it
** Author: @lszsrd
*/

// Used for strcmp() prototypes
#include <string.h>

#include "builtin.h"

/*
 * Variable: builtins_names
 * ------------------------
 * Defines handled builtin names
 */
const char *builtins_names[] = {
    "cd",
    "env",
    "exit",
    "setenv",
    "unsetenv",
    "set",
    "unset",
    "alias",
    "unalias",
    "history",
    "chdir",
    "printenv",
    "builtins",
    "echo",
    "!",
    NULL
};

/*
 * Variable: builtins
 * ------------------
 * Defines handled builtins' functions' pointers
 *
 * - shell: shell's structure
 * - argv: command parsed to a two dimensions strings array
 *
 * Returns: exit status of the pointed function
 */
int (*const builtins[]) (shell_t *shell, const char **argv) = {
    b_cd,
    b_env,
    b_exit,
    b_setenv,
    b_unsetenv,
    b_set,
    b_unset,
    b_alias,
    b_unalias,
    b_history,
    b_cd,
    b_printenv,
    b_builtins,
    b_echo,
    b_exclamation_mark
};

/*
 * Function: execute_builtin
 * -------------------------
 * Checks if given command is a builtin command, if so, executes it
 *
 * - argv: command splits into tokens
 *
 * Returns: above builtins()'s return value or 0 if no builtins correspond
 */
int execute_builtin(shell_t *shell, const ast_t *ast)
{
    for (int i = 0; builtins_names[i]; i++) {
        if (!strcmp(ast->command.argv[0], builtins_names[i])) {
            shell->status = builtins[i] (shell,
                (const char **) ast->command.argv);
            return (1);
        }
    }
    return (0);
}
