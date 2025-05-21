/*
** EPITECH PROJECT, 2024
** src/execution/builtins/b_alias.c
** File description:
** Sets a shell's alias
** Author: @lszsrd and @WilliamBSITT
*/

// Used for getpid() prototype
#include <unistd.h>
// Used for strncmp() prototype
#include <string.h>

#include "variables.h"
#include "builtin.h"

/*
 * Function: expand_variables
 * --------------------------
 * Searches for environment/local variables and print them
 *
 * - shell: shell's structure
 * - name: name to search
 *
 * Returns: length of the name on error, variable's value length otherwise
 */
static int expand_variables(shell_t *shell, const char *name)
{
    variable_t *node = get_variable(shell->heads->environment, name);

    shell->status = 0;
    if (node) {
        printf("%s", node->value);
        return (strlen(node->name) + 1);
    }
    node = get_variable(shell->heads->variables, name);
    if (node) {
        printf("%s", node->value);
        return (strlen(node->name) + 1);
    }
    dprintf(2, "%s: Undefined variable.", name);
    shell->status = 1;
    return (strlen(name) + 1);
}

/*
 * Function: parse_argument
 * ------------------------
 * Parses argument and do actions specific to flags, otherwise simply print
 *
 * - shell: shell's structure
 * - argument: current argument
 *
 * Returns: characters consumed
 */
static int parse_argument(shell_t *shell, const char *argument)
{
    if (!strncmp(argument, "$?", 2)) {
        printf("%d", shell->status);
        return (2);
    }
    if (!strncmp(argument, "$$", 2)) {
        printf("%d", getpid());
        return (2);
    }
    if (!strncmp(argument, "$_", 2)) {
        printf("%s", shell->last_argument);
        return (2);
    }
    if (argument[0] == '$' && argument[1]) {
        return (expand_variables(shell, &argument[1]));
    }
    printf("%c", argument[0]);
    return (1);
}

/*
 * Function: b_alias
 * -----------------
 * Sets a shell's alias
 *
 * - shell: shell's structure
 * - argv: command's arguments
 *
 * Returns: 0 on success, 1 otherwise
 */
int b_echo(shell_t *shell, const char **argv)
{
    for (int i = 1; argv[i]; i++) {
        for (int j = 0; argv[i][j];) {
            j += parse_argument(shell, &argv[i][j]);
        }
        if (argv[i + 1]) {
            printf(" ");
        }
    }
    printf("\n");
    return (0);
}
