/*
** EPITECH PROJECT, 2024
** src/shell/read_stream.c
** File description:
** Reads given stream
** Author: @lszsrd
*/

// Used for isatty() prototype
#include <unistd.h>
// Used for free() and exit() prototype
#include <stdlib.h>

#include "sncurses.h"
#include "shell.h"

/*
 * Function: read_stream
 * ---------------------
 * Reads standard input stream
 *
 * - shell: shell's structure
 *
 * Returns: allocated buffer containing standard input's last line
 */
char *read_stream(shell_t *shell)
{
    char *stdin_buffer = NULL;
    size_t buffer_size = 0;

    if (shell->use_ncurses) {
        reset_prog_mode();
        stdin_buffer = readline(shell);
        reset_shell_mode();
        return (stdin_buffer);
    }
    if (getline(&stdin_buffer, &buffer_size, stdin) == -1) {
        if (isatty(STDIN_FILENO)) {
            printf("exit\n");
        }
        free(stdin_buffer);
        exit(cleanup_shell((shell_t *) shell));
    }
    return (stdin_buffer);
}
