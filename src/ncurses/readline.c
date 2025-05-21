/*
** EPITECH PROJECT, 2024
** src/ncurses/readline.c
** File description:
** Reads standard input characters from a ncurses' window
** Author: @lszsrd, @HugoDuda and @Taoalex542
*/

// Used for calloc() prototype
#include <stdlib.h>
// Used for strerror() prototype
#include <string.h>
// Used for errno macro
#include <errno.h>

#include "sncurses.h"
#include "shell.h"

/*
 * Function: readline
 * ------------------
 * Retrieves stdin input from a ncurses window. Handles 4 arrow keys and
 *  delete key
 *
 * - history_head: head of the history linked list
 *
 * Returns: allocated buffer with user input or NULL on empty command
 */
char *readline(shell_t *shell)
{
    size_t prompt_length = display_ncurses_prompt(shell);
    char *stdin_input = calloc(MAX_INPUT_CHARACTERS, sizeof(char));
    int current_y_pos = getcury(stdscr);

    if (!stdin_input) {
        wprintw(stdscr, "calloc: %s", strerror(errno));
        return (NULL);
    }
    line_edition(shell->heads->history, &stdin_input, prompt_length);
    if (current_y_pos > 0) {
        wmove(stdscr, current_y_pos + 2, 0);
    } else {
        wmove(stdscr, current_y_pos + 1, 0);
    }
    refresh();
    if (!stdin_input[0]) {
        free(stdin_input);
        return (NULL);
    }
    return (stdin_input);
}
