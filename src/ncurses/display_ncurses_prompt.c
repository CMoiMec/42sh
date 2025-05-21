/*
** EPITECH PROJECT, 2024
** src/ncurses/display_ncurses_prompt.c
** File description:
** Displays prompt
** Author: @lszsrd
*/

// Used for passwd structure
#include <pwd.h>
// Used for getcwd() and getuid() prototypes
#include <unistd.h>
// Used for strncmp(), strlen() and strdup() prototypes
#include <string.h>
// Used for malloc() and free() prototypes
#include <stdlib.h>

#include "shell.h"
#include "sncurses.h"

/*
 * Function: display_prompt_parts
 * ------------------------------
 * Displays each parts of the prompt
 *
 * - prompt_length: length of the prompt
 * - user: current shell's user
 * - host hostname
 * - current_directory: currect active directory
 *
 * Returns: length of the prompt
 */
static size_t display_prompt_parts(size_t *prompt_length, char *user,
    char *host, char *current_directory)
{
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    *prompt_length += strlen(user);
    *prompt_length += strlen(host);
    *prompt_length += strlen(current_directory);
    wattron(stdscr, A_BOLD);
    wattron(stdscr, COLOR_PAIR(1));
    wprintw(stdscr, "%s@%s", user, host);
    wattroff(stdscr, COLOR_PAIR(1));
    wattroff(stdscr, A_BOLD);
    waddch(stdscr, ':');
    wattron(stdscr, A_BOLD);
    wattron(stdscr, COLOR_PAIR(2));
    wprintw(stdscr, "%s", current_directory);
    wattroff(stdscr, COLOR_PAIR(2));
    wattroff(stdscr, A_BOLD);
    wprintw(stdscr, " %% ");
    refresh();
    return (*prompt_length);
}

/*
 * Function: display_prompt
 * ------------------------
 * Displays customized prompt with last exit status, user, machine and current
 *  working directory
 *
 * - shell: shell's structure
 *
 * Returns: length of the prompt
 */
size_t display_ncurses_prompt(shell_t *shell)
{
    variable_t *home_var = get_variable(shell->heads->environment, "HOME");
    struct passwd *user = getpwuid(getuid());
    char *current_directory = NULL;
    char *host = malloc(sizeof(char) * 255);
    size_t prompt_length = 0;

    if (!host) {
        return (printf("%% "));
    }
    if (gethostname(host, 255) == -1) {
        free(host);
        host = strdup("42sh");
    }
    current_directory = (!home_var) ? getcwd(current_directory, 0)
        : transform_active_dir(getcwd(current_directory, 0), home_var->value);
    prompt_length = display_prompt_parts(&prompt_length, user->pw_name, host,
        current_directory);
    free(host);
    free(current_directory);
    return (5 + prompt_length);
}
