/*
** EPITECH PROJECT, 2024
** src/shell/main.c
** File description:
** Entry point of the 42sh program
** Author: @lszsrd
*/

// Used for isatty() prototype and STDIN_FILENO macro
#include <unistd.h>
// Used for free() prototype
#include <stdlib.h>

#include "sncurses.h"
#include "parser.h"
#include "execution.h"

/*
 * Function: main
 * --------------
 * Entry point of the 42sh program
 *
 * - argc: arguments count
 * - argv: arguments
 *
 * Returns: 84 if initialization failed, otherwise never directly returns
 */
int main(int argc, const char **argv)
{
    shell_t shell = {0};

    if (!parse_flags(argc, argv, &shell)) {
        return (0);
    }
    if (!initialize_shell(&shell)) {
        cleanup_shell(&shell);
        return (84);
    }
    do {
        if (isatty(STDIN_FILENO) && !shell.use_ncurses) {
            display_prompt(&shell);
        }
        shell.ast = parse_stream(&shell, read_stream(&shell));
        if (shell.ast) {
            expand_ast(&shell, shell.ast);
            release_ast(shell.ast);
            shell.ast = NULL;
        }
    } while ("If you don't struggle, you don't improve.");
}
