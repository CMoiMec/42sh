/*
** EPITECH PROJECT, 2024
** src/execution/commands/execute_command.c
** File description:
** Executes command or builtin stored in given AST
** Author: @lszsrd
*/

// Used for wait() prototype and W* macros
#include <sys/wait.h>
// Used for fork() prototype
#include <unistd.h>
// Used for strdup() prototypes
#include <string.h>
// Used for free() prototypes
#include <stdlib.h>
// Used for errno macro
#include <errno.h>

#include "execution.h"

/*
 * Function: register_exit_code
 * ----------------------------
 * Registers executed command's exit status as shell's exit status
 *
 * - shell: shell's structure
 *
 * Returns: exit status
 */
static int register_exit_code(shell_t *shell)
{
    int command_status = 0;

    wait(&command_status);
    shell->status = WEXITSTATUS(command_status);
    if (WIFSIGNALED(command_status) && !WIFSTOPPED(command_status)) {
        if (WTERMSIG(command_status) == SIGINT) {
            putc('\n', stdout);
            return (1);
        }
        shell->status = (128 + WTERMSIG(command_status));
        dprintf(2, "%s", strsignal(WTERMSIG(command_status)));
        if (WCOREDUMP(command_status)) {
            dprintf(2, " (core dumped)");
        }
        putc('\n', stderr);
    }
    return (shell->status);
}

/*
 * Function: syscall_execution
 * ---------------------------
 * Executes given AST with execve syscall
 *
 * - shell: shell's structure
 * - ast: an abstract syntax tree containing command to execute
 */
static void syscall_execution(shell_t *shell, const ast_t *ast)
{
    if (ast->command.binary) {
        execve(ast->command.binary, ast->command.argv, shell->environment);
        dprintf(2, "%s: %s.", ast->command.argv[0], strerror(errno));
        if (errno == ENOEXEC) {
            dprintf(2, WRONG_ARCHITECTURE);
        }
        putc('\n', stderr);
    }
    cleanup_shell(shell);
    exit(1);
}

/*
 * Function: execute_command
 * -------------------------
 * Executes command or builtin stored in given AST
 *
 * - shell: shell's structure
 * - ast: an abstract syntax tree containing command to execute
 */
void execute_command(shell_t *shell, const ast_t *ast, int register_status)
{
    int argc = 0;

    if (execute_builtin(shell, ast)) {
        return;
    }
    for (; ast->command.argv[argc]; argc++);
    free(shell->last_argument);
    shell->last_argument = strdup(ast->command.argv[argc - 1]);
    if (!check_command(shell, (ast_t *) ast)) {
        return;
    }
    shell->child = fork();
    if (shell->child == -1) {
        dprintf(2, "%s: %s.\n", ast->command.argv[0], strerror(errno));
        return;
    }
    if (shell->child == 0) {
        syscall_execution(shell, ast);
    }
    shell->status = (register_status) ? register_exit_code(shell) : 1;
}
