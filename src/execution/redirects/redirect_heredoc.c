/*
** EPITECH PROJECT, 2024
** src/execution/redirects/redirect_heredoc.c
** File description:
** Redirects here document to something
** Author: @lszsrd and @WilliamBSITT
*/

// Used for free() prototype
#include <stdlib.h>
// Used for dup2() prototype and STDIN/OUT_FILENO macros
#include <unistd.h>
// Used for strncmp() prototype
#include <string.h>

#include "shell.h"

/*
 * Function: redirect_heredoc
 * --------------------------
 * Redirects here document to something
 *
 * - shell: shell's structure
 * - ast: an abstract syntax tree containing command to execute
 *
 * Returns: 1 on success, 0 otherwise
 */
int redirect_heredoc(shell_t *shell, const ast_t *ast)
{
    FILE *heredoc = fopen("/tmp/temp", "w+");
    char *bf = NULL;
    int dup_result = -1;

    if (!heredoc) {
        shell->status = 1;
        perror("fopen");
        return (0);
    }
    printf("? ");
    for (size_t size = 0; getline(&bf, &size, stdin) != -1; printf("? ")) {
        if (!strncmp(bf, ast->command.argv[0], strlen(ast->command.argv[0]))) {
            break;
        }
        fprintf(heredoc, "%s", bf);
    }
    free(bf);
    dup_result = dup2(fileno(heredoc), STDIN_FILENO);
    fclose(heredoc);
    return ((dup_result == -1) ? 0 : 1);
}
