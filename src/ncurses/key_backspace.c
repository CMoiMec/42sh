/*
** EPITECH PROJECT, 2024
** src/ncurses/key_backspace.c
** File description:
** Erases a character at the cursor position
** Authors: @lszsrd, @HugoDuda and @Taoalex542
*/

// Used for strlen() prototype
#include <string.h>

#include "sncurses.h"

/*
 * Function: key_down
 * -------------------
 * Erases a character at the cursor position
 *
 * - history_node: current history node
 * - stdin_input: buffer containing current user input
 * - stdin_input_index: current stdin_input's index, matching the line's cursor
 * - prompt_length: length of the prompt
 */
void key_backspace(history_t **history_node, char **stdin_input,
    int *stdin_input_index, size_t prompt_length)
{
    char *buffer = *stdin_input;

    (void) history_node;
    (void) prompt_length;
    if (*stdin_input_index == 0) {
        beep();
        return;
    }
    for (int i = (*stdin_input_index); (*stdin_input)[i]; i++) {
        (*stdin_input)[i - 1] = buffer[i];
    }
    (*stdin_input_index) -= 1;
    (*stdin_input)[(*stdin_input_index)] = '\0';
    wmove(stdscr, getcury(stdscr), getcurx(stdscr) - 1);
    wdelch(stdscr);
    wrefresh(stdscr);
}
