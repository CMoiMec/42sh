/*
** EPITECH PROJECT, 2024
** src/execution/builtins/exclamation_mark.c
** File description:
** Displays shell's environ
** Author: @lszsrd
*/

#include "my.h"
#include "execution.h"
#include "builtin.h"

/*
 * Function: b_exclamation_mark
 * -----------------------------
 * Executes last command
 *
 * - shell: shell's structure
 * - argv: command's arguments
 *
 * Returns: executed command's exit status
 */
int b_exclamation_mark(shell_t *shell, const char **argv)
{
    history_t *histentry = shell->heads->history;

    (void) argv;
    while (histentry && histentry->command[0] == '!') {
        histentry = histentry->next;
    }
    if (!histentry) {
        return (0);
    }
    my_strfreev(shell->ast->command.argv);
    free(shell->ast->command.binary);
    free(shell->ast);
    shell->ast = parse_stream(shell, strdup(histentry->command));
    expand_ast(shell, shell->ast);
    return (shell->status);
}
