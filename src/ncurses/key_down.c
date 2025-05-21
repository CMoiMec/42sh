/*
** EPITECH PROJECT, 2024
** src/ncurses/key_down.c
** File description:
** Recalls next command in history
** Authors: @lszsrd, @HugoDuda and @Taoalex542
*/

// Used for memset() and strcpy() prototypes
#include <string.h>

#include "sncurses.h"

/*
 * Function: key_down
 * -------------------
 * Recalls previous command in history
 *
 * - history_node: current history node
 * - stdin_input: buffer containing current user input
 * - stdin_input_index: current stdin_input's index, matching the line's cursor
 * - prompt_length: length of the prompt
 */
void key_down(history_t **history_node, char **stdin_input,
    int *stdin_input_index, size_t prompt_length)
{
    char *old_input = *stdin_input;

    if (*history_node) {
        memset(*stdin_input, 0, MAX_INPUT_CHARACTERS);
        if ((*history_node)->prev) {
            strcpy(*stdin_input, (*history_node)->command);
            *history_node = (*history_node)->prev;
        } else {
            strcpy(*stdin_input, old_input);
            beep();
        }
        *stdin_input_index = strlen(*stdin_input);
        reset_current_line(stdin_input, prompt_length);
    } else {
        beep();
    }
}
