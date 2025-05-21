/*
** EPITECH PROJECT, 2024
** src/ncurses/key_left.c
** File description:
** Moves the cursor to the left
** Authors: @lszsrd, @HugoDuda and @Taoalex542
*/

#include "sncurses.h"

/*
 * Function: key_left
 * ------------------
 * Moves the cursor to the left
 *
 * - history_node: UNUSED
 * - stdin_input: UNUSED
 * - stdin_input_index: current stdin_input's index, matching the line's cursor
 * - prompt_length: length of the prompt
 */
void key_left(history_t **history_node, char **stdin_input,
    int *stdin_input_index, size_t prompt_length)
{
    size_t x = getcurx(stdscr);

    (void) history_node;
    (void) stdin_input;
    if (x > prompt_length) {
        *stdin_input_index -= 1;
        wmove(stdscr, getcury(stdscr), x - 1);
        refresh();
    } else {
        beep();
    }
}
