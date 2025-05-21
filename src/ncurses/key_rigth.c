/*
** EPITECH PROJECT, 2024
** src/ncurses/key_right.c
** File description:
** Moves the cursor to the right
** Authors: @lszsrd, @HugoDuda and @Taoalex542
*/

#include "sncurses.h"

/*
 * Function: key_right
 * -------------------
 * Moves the cursor to the right
 *
 * - history_node: current history node
 * - stdin_input: buffer containing current user input
 * - stdin_input_index: current stdin_input's index, matching the line's cursor
 * - prompt_length: length of the prompt
 */
void key_right(history_t **history_node, char **stdin_input,
    int *stdin_input_index, size_t prompt_length)
{
    size_t x = getcurx(stdscr);

    (void) history_node;
    (void) prompt_length;
    if (*stdin_input_index < (MAX_INPUT_CHARACTERS - 2)
        && (*stdin_input)[(*stdin_input_index)]) {
        (*stdin_input_index) += 1;
        wmove(stdscr, getcury(stdscr), x + 1);
        refresh();
    } else {
        beep();
    }
}
