/*
** EPITECH PROJECT, 2024
** src/execution/commands/check_command.c
** File description:
** Checks if given command is valid
** Author: @lszsrd
*/

// Used for stat structure and stat() prototype
#include <sys/stat.h>

#include "my.h"
#include "variables.h"
#include "execution.h"

/*
 * Function: check_for_globbins_replacement
 * ----------------------------------------
 * Expands globbins and reset AST's argv
 *
 * - ast: command's abstract syntax tree
 */
static void check_for_globbins_replacement(ast_t *ast)
{
    char *argv = NULL;

    for (int i = 0; ast->command.argv[i]; i++) {
        argv = expand_globbins(ast->command.binary, ast->command.argv[i]);
        if (argv) {
            break;
        }
    }
    if (argv) {
        if (argv[0]) {
            my_strfreev(ast->command.argv);
            ast->command.argv = my_str_to_word_array_escaper(argv, SEPARATORS);
        } else {
            dprintf(2, "%s: No match.\n", ast->command.argv[0]);
            free(ast->command.binary);
            ast->command.binary = NULL;
        }
    }
    free(argv);
}

/*
 * Function: check_access_rights
 * -----------------------------
 * Checks if given command exists and if it has execution permissions, if so,
 *  duplicates command to ast's data.binary field
 *
 * - ast: command's abstract syntax tree
 * - command: command to verify
 * - muted: turns on or off error messages
 *
 * Returns: 0 if an error occurred, 1 otherwise
 */
static int check_access_rights(ast_t *ast, const char *command, char muted)
{
    static struct stat sb;

    if (stat(command, &sb) == -1) {
        if (!muted) {
            dprintf(2, "%s: Command not found.\n", command);
        }
        return (0);
    }
    if (S_ISDIR(sb.st_mode)) {
        if (!muted) {
            dprintf(2, "%s: %s.\n", command, strerror(EACCES));
        }
        return (0);
    }
    if (ast) {
        free(ast->command.binary);
        ast->command.binary = my_strdup(command);
        check_for_globbins_replacement(ast);
    }
    return (1);
}

/*
 * Function: check_in_env_path
 * ---------------------------
 * Checks if given command, concatenated with an entry of PATH, exist
 *  Note: +2, on buffer's size, corresponds to '/' + '\0' additional characters
 *
 * - ast: command's abstract syntax tree
 * - path: a token of the PATH
 *
 * Returns: above check_access_rights()'s value
 */
static int check_in_env_path(ast_t *ast, const char *path)
{
    int result_value = 0;
    int path_length = strlen(path);
    int command_length = strlen(ast->command.argv[0]) + 2;
    char *buffer = malloc(sizeof(char) * (path_length + command_length));

    if (!buffer) {
        perror("malloc");
        return (0);
    }
    memset(buffer, 0, path_length + command_length);
    strcpy(buffer, path);
    buffer[path_length] = '/';
    strcat(&buffer[path_length] + 1, ast->command.argv[0]);
    result_value = check_access_rights(ast, buffer, true);
    free(buffer);
    return (result_value);
}

/*
 * Function: check_for_alias_replacement
 * -------------------------------------
 * Replaces AST's argv if it matches an alias
 *
 * - shell: shell's structure
 * - ast: command's abstract syntax tree
 */
static void check_for_alias_replacement(shell_t *shell, ast_t *ast)
{
    variable_t *alias = get_variable(shell->heads->aliases,
        ast->command.argv[0]);
    char *cmd = NULL;
    char *argv = NULL;

    if (alias) {
        cmd = my_word_array_to_str(&ast->command.argv[1]);
        if (!cmd) {
            return;
        }
        argv = malloc(sizeof(char) * (strlen(cmd) + strlen(alias->value) + 2));
        if (argv) {
            memset(argv, 0, strlen(cmd) + strlen(alias->value) + 2);
            strcat(strcat(strcat(argv, alias->value), " "), cmd);
            my_strfreev(ast->command.argv);
            ast->command.argv = my_str_to_word_array(argv, " \t");
            free(argv);
        }
    }
    free(cmd);
}

/*
 * Function: check_command
 * -----------------------
 * Checks if given command exists
 *
 * - shell: shell's structure
 * - ast: command's abstract syntax tree
 *
 * Returns: 1 if command exists and is executables, 0 otherwise
 */
int check_command(shell_t *shell, ast_t *ast)
{
    variable_t *environ_path = get_variable(shell->heads->environment, "PATH");
    char **path = NULL;

    check_for_alias_replacement(shell, ast);
    if (strchr(ast->command.argv[0], '/')) {
        return (check_access_rights(NULL, ast->command.argv[0], false));
    }
    if (environ_path) {
        path = my_str_to_word_array(environ_path->value, "=:\n");
    }
    for (int i = 0; path && path[i]; i++) {
        if (check_in_env_path(ast, path[i])) {
            my_strfreev(path);
            return (1);
        }
    }
    my_strfreev(path);
    dprintf(2, "%s: Command not found.\n", ast->command.argv[0]);
    shell->status = 1;
    return (0);
}
