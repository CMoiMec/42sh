/*
** EPITECH PROJECT, 2024
** src/execution/builtins/builtins.c
** File description:
** Lists available builtins
** Author: @WilliamBSITT
*/

#include "builtin.h"

/*
 * Variable: builtins_names
 * ------------------------
 * Looks up for builtins string array variable definition from
 *  'commands/execute_builtin.c' file
 */
extern char *builtins_names[];

/*
 * Function: b_builtins
 * --------------------
 * Lists available builtins
 *
 * - shell: shell's structure
 * - argv: command's arguments
 *
 * Returns: 0
 */
int b_builtins(shell_t *shell, const char **argv)
{
    (void) shell;
    (void) argv;
    for (int i = 0; builtins_names[i]; i++) {
        printf("%s\n", builtins_names[i]);
    }
    return (0);
}
