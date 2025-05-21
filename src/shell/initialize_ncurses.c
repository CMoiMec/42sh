/*
** EPITECH PROJECT, 2024
** src/shell/initialize_ncurses.c
** File description:
** Initializes ncurses' window
** Authors: @lszsrd, @HugoDuda and @Taoalex542
*/

// Used for ncurses' prototypes
#include <ncurses.h>

#include "shell.h"

/*
 * Function: initialize_ncurses
 * ----------------------------
 * Initializes ncurses' window
 *
 * - shell: shell's structure
 *
 * Returns: 0 on errors, 1 otherwise
 */
int initialize_ncurses(shell_t *shell)
{
    if (!initscr()) {
        perror("initscr");
        return (0);
    }
    if (!has_colors()) {
        endwin();
        dprintf(2, "This terminal doesn't support colors.\n");
        return (0);
    }
    noecho();
    cbreak();
    keypad(stdscr, true);
    scrollok(stdscr, true);
    shell->use_ncurses = 1;
    start_color();
    reset_prog_mode();
    return (1);
}
