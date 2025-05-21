/*
** EPITECH PROJECT, 2024
** src/execution/builtins/b_exit.c
** File description:
** Exits shell
** Author: @lszsrd
*/

// Used for isatty() prototyype and STDIN_FILENO macro
#include <unistd.h>
// Used for strcmp() prototype
#include <string.h>
// Used for atoi() and exit() prototype
#include <stdlib.h>

#include "builtin.h"

/*
 * Function: b_exit
 * ----------------
 * Terminates shell
 *
 * - shell: shell's structure
 * - argv: command's arguments
 *
 * Returns: shell's last exit status or aborts exit process and returns 1
 */
int b_exit(shell_t *shell, const char **argv)
{
    int status = 0;

    if (argv[1]) {
        status = atoi(argv[1]);
        if (!status && strcmp(argv[1], "0") && strcmp(argv[1], "-0")) {
            dprintf(2, "%s: Expression Syntax.\n", argv[0]);
            return (1);
        }
        shell->status = (status % 256);
    }
    if (isatty(STDIN_FILENO)) {
        printf("exit\n");
    }
    exit(cleanup_shell(shell));
}
