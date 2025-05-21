/*
** EPITECH PROJECT, 2024
** src/execution/redirects/redirect_pipe.c
** File description:
** Pipes a command to another one
** Author: @lszsrd
*/

// Used for wait() prototype
#include <sys/wait.h>
// Used for dup2() prototype and STDIN/OUT_FILENO macros
#include <unistd.h>
// Used for exit() prototype
#include <stdlib.h>

#include "execution.h"

/*
 * Function: execute_pipe
 * ----------------------
 * Sets left pipe operand and execute its command on "NO WAIT" mode (disabling
 *  registering exit status).
 *
 * - shell: shell's structure
 * - ast: an abstract syntax tree containing command to pipe
 */
static void execute_pipe(shell_t *shell, const ast_t *ast)
{
    int previous_fds[2] = {shell->fds->pipe[0], shell->fds->pipe[1]};
    pid_t child = -1;

    if (pipe(shell->fds->pipe) != -1) {
        child = fork();
    }
    close(previous_fds[1]);
    if (child == -1) {
        return;
    }
    if (child == 0) {
        if (dup2(previous_fds[0], STDIN_FILENO) == -1
            || dup2(shell->fds->pipe[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            close(previous_fds[0]);
        }
        execute_command(shell, ast, 0);
        exit(cleanup_shell(shell));
    }
    wait(NULL);
}

/*
 * Function: redirect_pipe
 * -----------------------
 * Pipes a command to another one
 *  Note: we call recursively above function to fork and execute each pipe.
 *  We then redirect pipe's file descriptor to STDIN, revert back default
 *  STDOUT, execute the last pending command and then reverting STDOUT
 *
 * - shell: shell's structure
 * - ast: an abstract syntax tree containing command to pipe
 *
 * Returns: 0 on errors, 1 otherwise
 */
int redirect_pipe(shell_t *shell, const ast_t *ast)
{
    if (ast->type == REDIRECT && ast->redirect.type == PIPE) {
        execute_pipe(shell, ast->redirect.left);
        return (redirect_pipe(shell, ast->redirect.right));
    }
    close(shell->fds->pipe[1]);
    if (dup2(shell->fds->pipe[0], STDIN_FILENO) == -1
        || dup2(shell->fds->standard[1], STDOUT_FILENO) == -1) {
        perror("dup2");
    } else {
        close(shell->fds->pipe[0]);
        expand_ast(shell, ast);
    }
    if (dup2(shell->fds->standard[0], STDIN_FILENO) == -1) {
        perror("dup2");
        exit(cleanup_shell(shell));
    }
    return (1);
}
