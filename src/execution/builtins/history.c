/*
** EPITECH PROJECT, 2024
** src/execution/builtins/b_history.c
** File description:
** Displays shell's history
** Author: @lszsrd and @WilliamBSITT
*/

// Used for strcmp() prototype
#include <string.h>

#include "builtin.h"

/*
 * Function: b_history
 * -------------------
 * Displays or deletes history
 *
 * - shell: shell's structure
 * - argv: command's arguments
 *
 * Returns: 0
 */
int b_history(shell_t *shell, const char **argv)
{
    history_t *histentry = shell->heads->history;

    if (argv[1] && !strcmp(argv[1], "-c")) {
        release_history_entries(&shell->heads->history);
        return (0);
    }
    for (; histentry->next; histentry = histentry->next);
    for (int i = 1; histentry; i++) {
        printf("\t%d  %s\t%s\n", i, histentry->timestamp, histentry->command);
        histentry = histentry->prev;
    }
    return (0);
}
