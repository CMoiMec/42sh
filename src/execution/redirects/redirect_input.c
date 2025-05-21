/*
** EPITECH PROJECT, 2024
** src/execution/redirects/redirect_input.c
** File description:
** Redirects input from something to something else
** Author: @lszsrd
*/

// Used for open() prototype
#include <fcntl.h>
// Used for close() prototype
#include <unistd.h>
// Used for strerror() prototype
#include <string.h>
// Used for errno macro
#include <errno.h>

#include "shell.h"

/*
 * Function: redirect_input
 * ------------------------
 * Redirects input from something to something else. It is calling function's
 *  responsibility to revert back standard flux after command execution
 *
 * - shell: shell's structure
 * - ast: an abstract syntax tree containing command to execute
 *
 * Returns: 1 on success, 0 otherwise
 */
int redirect_input(shell_t *shell, const ast_t *ast)
{
    int fd = open(ast->command.argv[0], O_RDONLY);

    if (fd == -1 || dup2(fd, STDIN_FILENO) == -1) {
        shell->status = 1;
        dprintf(2, "%s: %s.\n", ast->command.argv[0], strerror(errno));
        if (fd != -1) {
            close(fd);
        }
        return (0);
    }
    close(fd);
    return (1);
}
