/*
** EPITECH PROJECT, 2024
** src/execution/builtins/b_unset.c
** File description:
** Un-sets a shell's local variable
** Author: @lszsrd and @WilliamBSITT
*/

#include "builtin.h"

/*
 * Function: b_unsetenv
 * --------------------
 * Un-sets a shell's local variable
 *
 * - shell: shell's structure
 * - argv: command's arguments
 *
 * Returns: 0 on success, 1 otherwise
 */
int b_unset(shell_t *shell, const char **argv)
{
    if (!argv[1]) {
        dprintf(2, "%s: Too few arguments.\n", argv[0]);
        return (1);
    }
    for (int i = 1; argv[i]; i++) {
        unset_variable(&shell->heads->variables, argv[i]);
    }
    return (0);
}
