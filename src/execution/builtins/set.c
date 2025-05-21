/*
** EPITECH PROJECT, 2024
** src/execution/builtins/b_set.c
** File description:
** Sets a shell's local variable
** Author: @lszsrd and @WilliamBSITT
*/

// Used for isalpha() prototype
#include <ctype.h>
// Used for strcmp() and strchr() prototypes
#include <string.h>

#include "builtin.h"

/*
 * Function: display_variables
 * ---------------------------
 * Displays shell's local variable
 *
 * - shell: shell's structure
 */
static void display_variables(shell_t *shell)
{
    variable_t *variable = shell->heads->variables;

    while (variable) {
        printf("%s\t%s\n", variable->name, variable->value);
        variable = variable->next;
    }
}

/*
 * Function: check_only_alphanum
 * ---------------------------
 * Check if every caracters is an alphanum caracters
 *
 * - shell: shell's structure
 */
static int check_only_alphanum(const char **argv, int i)
{
    for (int e = 0; argv[i][e]; e++) {
        if (!isalnum(argv[i][e]) && !strchr("._", argv[i][e]) &&
            argv[i][e] != '=') {
            dprintf(2, "%s: Variable name must contain alphanumeric"
                " characters.\n", argv[0]);
            return (1);
        }
    }
    return (0);
}

/*
 * Function: b_setenv
 * ------------------
 * Sets a shell's local variable
 *
 * - shell: shell's structure
 * - argv: command's arguments
 *
 * Returns: 0 on success, 1 otherwise
 */
int b_set(shell_t *shell, const char **argv)
{
    if (!argv[1]) {
        display_variables(shell);
        return (0);
    }
    for (int i = 1; argv[i]; i++) {
        if (!isalpha(argv[i][0])) {
            dprintf(2, "%s: Variable name must begin with a letter.\n",
                argv[0]);
            return (1);
        }
        if (check_only_alphanum(argv, i))
            return (1);
        if (argv[i + 1] && !strcmp(argv[i + 1], "=")) {
            set_variable(&shell->heads->variables, argv[i], argv[i + 2]);
            i += (argv[i + 2]) ? 2 : 1;
        } else {
            set_variable(&shell->heads->variables, argv[i], NULL);
        }
    }
    return (0);
}
