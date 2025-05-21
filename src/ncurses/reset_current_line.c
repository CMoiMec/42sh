/*
** EPITECH PROJECT, 2024
** src/ncurses/reset_current_line.c
** File description:
** Erases characters of the line and reprints stdin_input
** Authors: @lszsrd, @HugoDuda and @Taoalex542
*/

// Used for memset() and strcpy() prototypes
#include <string.h>

#include "sncurses.h"

/*
 * Function: reset_current_line
 * ----------------------------
 * Erases characters of the line and reprints stdin_input
 *
 * - stdin_input: buffer containing current user input
 * - prompt_length: length of the prompt
 */
void reset_current_line(char **stdin_input, size_t prompt_length)
{
    mvwprintw(stdscr, getcury(stdscr), prompt_length, "%s", *stdin_input);
    for (int x = getcurx(stdscr); x < getmaxx(stdscr); x++) {
        wdelch(stdscr);
    }
    refresh();
}
