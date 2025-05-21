/*
** EPITECH PROJECT, 2024
** src/shell.h
** File description:
** Defines shell's ncurses ('s' stands for shell in 'sncurses.h') structure
**  and prototypes
** Authors: @lszsrd, @HugoDuda and @Taoalex542
*/

#pragma once

// Used for ncurses' prototypes
#include <ncurses.h>

#include "history.h"

/*
 * Macro: MAX_INPUT_CHARACTERS
 * ---------------------------
 * Defines max input length
 */
#define MAX_INPUT_CHARACTERS 1024

/*
 * Structure: shell_t
 * ------------------
 * Redefinition of shell's structure prototype as we cannot include "shell.h"
 *  due to circular imports
 */
typedef struct shell_s shell_t;

/*
 * Prototypes definition
 */

char *readline(shell_t *shell);

size_t display_ncurses_prompt(shell_t *shell);

void line_edition(history_t *history_node, char **stdin_input,
    size_t prompt_length);
void add_character_to_input_buffer(char **stdin_input,
    int *stdin_input_index, size_t prompt_length, int key);
void reset_current_line(char **stdin_input, size_t prompt_length);

void register_character(history_t **history_node, char **stdin_input,
    int *stdin_input_index, size_t prompt_length);
void key_up(history_t **history_node, char **stdin_input,
    int *stdin_input_index, size_t prompt_length);
void key_down(history_t **history_node, char **stdin_input,
    int *stdin_input_index, size_t prompt_length);
void key_left(history_t **history_node, char **stdin_input,
    int *stdin_input_index, size_t prompt_length);
void key_right(history_t **history_node, char **stdin_input,
    int *stdin_input_index, size_t prompt_length);
void key_backspace(history_t **history_node, char **stdin_input,
    int *stdin_input_index, size_t prompt_length);
