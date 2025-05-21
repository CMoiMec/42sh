/*
** EPITECH PROJECT, 2024
** src/execution/builtins/b_env.c
** File description:
** Displays shell's environ
** Author: @lszsrd
*/

#include "builtin.h"

/*
 * Function: b_env
 * ---------------
 * Displays shell's environ
 *
 * - shell: shell's structure
 * - argv: command's arguments
 *
 * Returns: 0
 */
int b_env(shell_t *shell, const char **argv)
{
    variable_t *env_variable = shell->heads->environment;

    (void) argv;
    while (env_variable) {
        printf("%s=%s\n", env_variable->name, env_variable->value);
        env_variable = env_variable->next;
    }
    return (0);
}
