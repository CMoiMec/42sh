/*
** EPITECH PROJECT, 2024
** src/ncurses/add_character_to_input_buffer.c
** File description:
** Adds a character to the stdin_input at stdin_input_index position
** Authors: @lszsrd, @HugoDuda and @Taoalex542
*/

// Used for strlen() prototype
#include <string.h>

#include "sncurses.h"

/*
 * Function: add_character_to_input_buffer
 * ---------------------------------------
 * Adds a character to the stdin_input at stdin_input_index position
 *
 * - stdin_input: buffer containing current user input
 * - stdin_input_index: current stdin_input's index, matching the line's cursor
 * - prompt_length: length of the prompt
 * - key: retrieved character
 */
void add_character_to_input_buffer(char **stdin_input,
    int *stdin_input_index, size_t prompt_length, int key)
{
    char *buffer_at_old_index = &(*stdin_input)[(*stdin_input_index)];
    int current_x_pos = getcurx(stdscr);
    size_t buffer_len = strlen((*stdin_input));

    if ((size_t) (*stdin_input_index) < buffer_len) {
        for (size_t i = (*stdin_input_index); i < buffer_len; i++) {
            (*stdin_input)[i + 1] = (*stdin_input)[i];
        }
        (*stdin_input)[(*stdin_input_index)] = (char) key;
    } else {
        (*stdin_input)[(*stdin_input_index)] = (char) key;
        for (size_t i = 0; buffer_at_old_index[i]; i++) {
            (*stdin_input)[(*stdin_input_index) + i] = buffer_at_old_index[i];
        }
    }
    (*stdin_input_index) += 1;
    reset_current_line(stdin_input, prompt_length);
    wmove(stdscr, getcury(stdscr), current_x_pos);
}
