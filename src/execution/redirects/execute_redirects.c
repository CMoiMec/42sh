/*
** EPITECH PROJECT, 2024
** src/execution/redirects/execute_redirects.c
** File description:
** Executes redirects of the given AST
** Author: @lszsrd
*/

// Used for dup2() prototype and STDIN/OUT_FILENO macros
#include <unistd.h>

#include "execution.h"

/*
 * Variable: redirects
 * -------------------
 * Defines redirects' functions' pointers based on redirect_t (see lexer.h)
 *
 * - shell: shell's structure
 * - argv: command parsed to a strings array
 *
 * Returns: exit status of the pointed function
 */
static int (*const redirects[]) (shell_t *shell, const ast_t *ast) = {
    redirect_append,
    redirect_output,
    redirect_pipe,
    redirect_heredoc,
    redirect_input
};

/*
 * Function: expand_redirects
 * --------------------------
 * Expands redirects and call appropriate module given the previous redirect
 *  type
 *
 * - ast: an abstract syntax tree containing redirect to execute
 * - type: previous redirect type
 *
 * Returns: 1 on success, 0 otherwise
 */
static int expand_redirects(shell_t *shell, const ast_t *ast, redirect_t type)
{
    if (!ast) {
        return (0);
    }
    if (ast->type == REDIRECT) {
        if (type == PIPE) {
            return (expand_redirects(shell, ast->redirect.right,
                ast->redirect.type));
        }
        if (expand_redirects(shell, ast->redirect.right, ast->redirect.type)) {
            return (redirects[type] (shell, ast->redirect.left));
        } else {
            return (0);
        }
    }
    if (type == PIPE) {
        return (0);
    } else {
        return (redirects[type] (shell, ast));
    }
}

/*
 * Function: execute_redirects
 * ---------------------------
 * Executes command or builtin stored in given AST
 *
 * - shell: shell's structure
 * - ast: an abstract syntax tree containing command to execute
 */
void execute_redirects(shell_t *shell, const ast_t *ast)
{
    ast_t *command = ast->redirect.left;

    if (ast->redirect.type == PIPE) {
        expand_redirects(shell, ast->redirect.right, ast->redirect.type);
        if (pipe(shell->fds->pipe) == -1) {
            perror("pipe");
        } else {
            redirects[PIPE] (shell, ast);
        }
        return;
    }
    if (expand_redirects(shell, ast->redirect.right, ast->redirect.type)) {
        execute_command(shell, command, 1);
    }
    if (dup2(shell->fds->standard[0], STDIN_FILENO) == -1
        || dup2(shell->fds->standard[1], STDOUT_FILENO) == -1) {
            perror("dup2");
    }
}
