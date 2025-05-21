/*
** EPITECH PROJECT, 2024
** src/execution/builtins/b_setenv.c
** File description:
** Sets a shell's environment variable
** Author: @lszsrd
*/

// Used for isalpha() prototype
#include <ctype.h>
// Used for strchr() prototypes
#include <string.h>

#include "builtin.h"

/*
 * Function: b_setenv
 * ------------------
 * Sets a shell's environ variable
 *
 * - shell: shell's structure
 * - argv: command's arguments
 *
 * Returns: 0 on success, 1 otherwise
 */
int b_setenv(shell_t *shell, const char **argv)
{
    if (!argv[1]) {
        return (b_env(shell, argv));
    }
    if (!isalpha(argv[1][0])) {
        dprintf(2, "%s: Variable name must begin with a letter.\n", argv[0]);
        return (1);
    }
    if (argv[2] && argv[3]) {
        dprintf(2, "%s: Too many arguments.\n", argv[0]);
        return (1);
    }
    for (int i = 0; argv[1][i]; i++) {
        if (!isalnum(argv[1][i]) && !strchr("._", argv[1][i])) {
            dprintf(2, "%s: Variable name must contain alphanumeric"
                " characters.\n", argv[0]);
            return (1);
        }
    }
    set_variable(&shell->heads->environment, argv[1], argv[2]);
    return (update_environment(shell));
}
