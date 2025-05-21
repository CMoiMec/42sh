/*
** EPITECH PROJECT, 2024
** src/shell/cleanup_shell.c
** File description:
** Releases shell's structure memory
** Author: @lszsrd
*/

// Used for endwin() prototype
#include <ncurses.h>

#include "my.h"
#include "shell.h"

/*
 * Function: release_variables
 * ---------------------------
 * Releases still allocated memory of a variable_t linked list
 *
 * - head: linked list's head to release
 */
void release_variables(variable_t *head)
{
    variable_t *variable = head;
    variable_t *releasing_node = NULL;

    while (variable) {
        releasing_node = variable;
        variable = variable->next;
        free(releasing_node->name);
        free(releasing_node->value);
        free(releasing_node);
    }
}

/*
 * Function: release_history_entries
 * ---------------------------------
 * Releases shell's history entries, may also be used during shell's lifetime
 *
 * - shell: shell's structure
 */
void release_history_entries(history_t **head)
{
    history_t *history_entry = *head;
    history_t *releasing_node = NULL;

    while (history_entry) {
        releasing_node = history_entry;
        history_entry = history_entry->next;
        free(releasing_node->command);
        free(releasing_node->timestamp);
        free(releasing_node);
    }
    *head = NULL;
}

/*
 * Function: cleanup_shell
 * -----------------------
 * Releases still allocated memory at shell's exit
 *
 * - shell: shell's structure
 *
 * Returns: shell's last exit status
 */
int cleanup_shell(shell_t *shell)
{
    release_ast(shell->ast);
    shell->ast = NULL;
    release_variables(shell->heads->environment);
    release_variables(shell->heads->variables);
    release_variables(shell->heads->aliases);
    release_history_entries(&shell->heads->history);
    free(shell->heads);
    close(shell->fds->standard[0]);
    close(shell->fds->standard[1]);
    free(shell->fds);
    my_strfreev(shell->environment);
    free(shell->last_argument);
    if (shell->use_ncurses) {
        endwin();
        _nc_free_and_exit(shell->status);
    }
    return (shell->status);
}
