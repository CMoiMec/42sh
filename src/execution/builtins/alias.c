/*
** EPITECH PROJECT, 2024
** src/execution/builtins/b_alias.c
** File description:
** Sets a shell's alias
** Author: @lszsrd and @WilliamBSITT
*/

#include "my.h"
#include "builtin.h"

/*
 * Function: display_aliases
 * -------------------------
 * Shows shell's aliases
 *
 * - shell: shell's structure
 */
static void display_aliases(shell_t *shell)
{
    variable_t *alias = shell->heads->aliases;
    char **argv = NULL;

    for (; alias; alias = alias->next) {
        printf("%s\t", alias->name);
        argv = my_str_to_word_array(alias->value, " \t");
        if (!argv) {
            continue;
        }
        if (argv[1]) {
            putc('(', stdout);
        }
        for (int i = 0; argv[i]; i++) {
            printf("%s%s", argv[i], (argv[i + 1]) ? " " : "");
        }
        printf("%s\n", (argv[1]) ? ")" : "");
        my_strfreev(argv);
    }
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
int b_alias(shell_t *shell, const char **argv)
{
    char *alias = NULL;
    variable_t *node = shell->heads->aliases;

    if (!argv[1]) {
        display_aliases(shell);
        return (0);
    }
    if (!argv[2]) {
        node = get_variable(node, argv[1]);
        if (node)
            printf("%s\n", node->value);
        return (0);
    }
    alias = my_word_array_to_str((char **) &argv[2]);
    if (!alias) {
        return (1);
    }
    set_variable(&shell->heads->aliases, argv[1], alias);
    free(alias);
    return (0);
}
