/*
** EPITECH PROJECT, 2024
** src/ncurses/readline.c
** File description:
** Reads standard input characters from a ncurses' window
** Authors: @lszsrd, @HugoDuda and @Taoalex542
*/

#include "sncurses.h"

/*
 * Variable: keys
 * --------------
 * Defines handled keys for line edition
 */
static const int keys[] = {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_BACKSPACE, -1
};

/*
 * Variable: line_actions
 * ----------------------
 * Defines line edition actions' functions' pointers
 *
 * - history_node: current history node
 * - stdin_input: buffer containing current user input
 * - stdin_input_index: current stdin_input's index, matching the line's cursor
 * - prompt_length: length of the prompt
 */
static void (*const line_actions[]) (history_t **history_node,
    char **stdin_input, int *stdin_input_index, size_t prompt_length) = {
    key_up, key_down, key_left, key_right, key_backspace
};

/*
 * Function: get_action_to_perform
 * -------------------------------
 * Gets action to perform function's id based on received character
 *
 * - key: reiceived character
 *
 * Returns: a function pointer id
 */
static int get_action_to_perform(int key)
{
    for (int i = 0; keys[i] != -1; i++) {
        if (key == keys[i]) {
            return (i);
        }
    }
    return (-1);
}

/*
 * Function: line_edition
 * ----------------------
 * Gets each characters user gives to the keyboard and mergs them to a buffer
 *
 * - history_node: current history node
 * - stdin_input: buffer containing current user input
 * - prompt_length: length of the prompt
 */
void line_edition(history_t *history_node, char **stdin_input,
    size_t prompt_length)
{
    int stdin_input_index = 0;
    int function_index = -1;

    for (int key = wgetch(stdscr); key != '\n'; key = wgetch(stdscr)) {
        function_index = get_action_to_perform(key);
        if (function_index == -1) {
            waddch(stdscr, key);
            add_character_to_input_buffer(stdin_input, &stdin_input_index,
                prompt_length, key);
        } else {
            line_actions[function_index] (&history_node, stdin_input,
                &stdin_input_index, prompt_length);
        }
    }
}
