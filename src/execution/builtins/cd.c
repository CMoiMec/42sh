/*
** EPITECH PROJECT, 2024
** src/execution/builtins/cd.c
** File description:
** Changes shell's current working directory
** Author: @lszsrd
*/

// Used for chdir() prototype
#include <unistd.h>
// Used for free() prototype
#include <stdlib.h>
// Used for strcmp() and strerror() prototypes
#include <string.h>
// Used for errno macro
#include <errno.h>

#include "builtin.h"

/*
 * Function: update_pwd_and_oldpwd
 * -------------------------------
 * Updates shell's PWD and OLDPWD environment variables
 *
 * - shell: shell's structure
 * - oldpwd: old current working directory
 *
 * Returns: 0 on success, 1 otherwise
 */
static int set_pwd_and_oldpwd(shell_t *shell, char *oldpwd)
{
    char *pwd = NULL;

    pwd = getcwd(pwd, 0);
    set_variable(&shell->heads->environment, "PWD", pwd);
    set_variable(&shell->heads->environment, "OLDPWD", oldpwd);
    free(pwd);
    free(oldpwd);
    return (update_environment(shell));
}

/*
 * Function: set_home_directory
 * ----------------------------
 * Sets shell's current directory to user's home
 *
 * - shell: shell's structure
 * - oldpwd: old current working directory
 *
 * Returns: 0 on success, 1 otherwise
 */
static int set_home_directory(shell_t *shell, const char **argv, char *oldpwd)
{
    variable_t *env_home = get_variable(shell->heads->environment, "HOME");

    if (!env_home) {
        dprintf(2, "%s: No home directory.\n", argv[0]);
        free(oldpwd);
        return (1);
    }
    if (chdir(env_home->value) == -1) {
        dprintf(2, "%s: %s.\n", env_home->value, strerror(errno));
        free(oldpwd);
        return (1);
    }
    return (set_pwd_and_oldpwd(shell, oldpwd));
}

/*
 * Function: set_oldpwd_directory
 * ------------------------------
 * Sets shell's current directory to previous visited directory
 *
 * - shell: shell's structure
 * - arg: given argument
 * - oldpwd: old current working directory
 *
 * Returns: 0 on success, 1 otherwise
 */
static int set_oldpwd_directory(shell_t *shell, const char **argv,
    char *oldpwd)
{
    variable_t *env_oldpwd = get_variable(shell->heads->environment, "OLDPWD");

    if (strcmp(argv[1], "-")) {
        dprintf(2, "Usage: %s [-plvn][-|<dir>].\n", argv[0]);
        free(oldpwd);
        return (1);
    }
    if (!env_oldpwd) {
        dprintf(2, ": No such file or directory.\n");
        free(oldpwd);
        return (1);
    }
    if (chdir(env_oldpwd->value) == -1) {
        dprintf(2, "%s: %s.\n", env_oldpwd->value, strerror(errno));
        free(oldpwd);
        return (1);
    }
    return (set_pwd_and_oldpwd(shell, oldpwd));
}

/*
 * Function: b_cd
 * --------------
 * Changes shell's current working directory
 *
 * - shell: shell's structure
 * - argv: command's arguments
 *
 * Returns: 0 on success, 1 otherwise
 */
int b_cd(shell_t *shell, const char **argv)
{
    char *oldpwd = NULL;

    oldpwd = getcwd(oldpwd, 0);
    if (!argv[1] || !strcmp(argv[1], "~")) {
        return (set_home_directory(shell, argv, oldpwd));
    }
    if (argv[1][0] == '-') {
        return (set_oldpwd_directory(shell, argv, oldpwd));
    }
    if (argv[2]) {
        dprintf(2, "%s: Too many arguments.\n", argv[0]);
        free(oldpwd);
        return 1;
    }
    if (chdir(argv[1]) == -1) {
        dprintf(2, "%s: %s.\n", argv[1], strerror(errno));
        free(oldpwd);
        return (1);
    }
    return (set_pwd_and_oldpwd(shell, oldpwd));
}
