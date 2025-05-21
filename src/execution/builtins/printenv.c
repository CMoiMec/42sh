/*
** EPITECH PROJECT, 2024
** src/execution/builtins/b_printenv.c
** File description:
** Prints an element of the environment
** Author: @WilliamBSITT
*/

#include "builtin.h"

/*
 * Function: b_printenv
 * --------------------
 * Prints an element of the environment
 *
 * - shell: shell's structure
 * - argv: command's arguments
 *
 * Returns: 0 on success, 1 otherwisee
 */
int b_printenv(shell_t *shell, const char **argv)
{
    variable_t *node = NULL;

    if (!argv[1]) {
        return (b_env(shell, argv));
    }
    if (!argv[2]) {
        node = get_variable(shell->heads->environment, argv[1]);
        if (node) {
            printf("%s\n", node->value);
        }
        return (0);
    }
    printf("%s: Too many arguments.\n", argv[0]);
    return (1);
}
