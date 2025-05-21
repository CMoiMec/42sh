/*
** EPITECH PROJECT, 2024
** src/ncurses/key_up.c
** File description:
** Recalls next command in history
** Authors: @lszsrd, @HugoDuda and @Taoalex542
*/

// Used for memset() and strcpy() prototypes
#include <string.h>

#include "sncurses.h"

/*
 * Function: key_up
 * -------------------
 * Recalls next command in history
 *
 * - history_node: current history node
 * - stdin_input: buffer containing current user input
 * - stdin_input_index: current stdin_input's index, matching the line's cursor
 * - prompt_length: length of the prompt
 */
void key_up(history_t **history_node, char **stdin_input,
    int *stdin_input_index, size_t prompt_length)
{
    history_t *save = *history_node;

    if (*history_node) {
        memset(*stdin_input, 0, MAX_INPUT_CHARACTERS);
        strcpy(*stdin_input, (*history_node)->command);
        *history_node = (*history_node)->next;
        if (!*history_node) {
            *history_node = save;
            beep();
        }
        *stdin_input_index = strlen(*stdin_input);
        reset_current_line(stdin_input, prompt_length);
    } else {
        beep();
    }
}
