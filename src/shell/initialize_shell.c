/*
** EPITECH PROJECT, 2024
** src/shell/initialize_shell.c
** File description:
** Initializes shell's structure
** Author: @lszsrd
*/

// Used for signal() prototype
#include <signal.h>
// Used for open() prototype
#include <fcntl.h>
// Used for errno macro
#include <errno.h>
// Used for strlen() prototype
#include <string.h>

#include "my.h"
#include "shell.h"

/*
 * Variable: environ
 * -----------------
 * Looks up for environ's strings array variable definition from standard libC
 */
extern char **environ;

/*
 * Function: signal_handler
 * ------------------------
 * Catches SIGINT (CTRL. C) signal and ignores it
 *
 * - signal_id: caught signal's number
 */
static void signal_handler(int signal_id)
{
    (void) signal_id;
}

/*
 * Function: update_environment
 * ----------------------------
 * Safely updates shell's environment
 *
 * - shell: shell's structure
 *
 * Returns: 0 if environment has been updated, 1 otherwise
 */
int update_environment(shell_t *shell)
{
    char **new_environment = convert_environment(shell->heads->environment);

    if (!new_environment) {
        return (1);
    }
    my_strfreev(shell->environment);
    shell->environment = new_environment;
    return (0);
}

/*
 * Function: set_shell_head_nodes
 * ------------------------------
 * Sets shell's head's linked lists' nodes
 *
 * - shell: shell's structure
 *
 * Returns: 1 on success, 0 otherwise
 */
static int set_shell_head_nodes(shell_t *shell)
{
    shell->heads = malloc(sizeof(linked_list_head_t));
    if (!shell->heads) {
        perror("malloc");
        return (0);
    }
    shell->heads->environment = create_environment(environ);
    shell->heads->variables = NULL;
    shell->heads->aliases = NULL;
    shell->heads->history = NULL;
    return (1);
}

/*
 * Function: set_shell_standard_fds
 * --------------------------------
 * Sets shell's standard input and ouput
 *
 * - shell: shell's structure
 *
 * Returns: 1 on success, 0 otherwise
 */
static int set_shell_standard_fds(shell_t *shell)
{
    shell->fds = malloc(sizeof(file_descriptors_t));
    if (!shell->fds) {
        perror("malloc");
        return (0);
    }
    shell->fds->standard[0] = dup(STDIN_FILENO);
    shell->fds->standard[1] = dup(STDOUT_FILENO);
    if (shell->fds->standard[0] == -1 || shell->fds->standard[1] == -1) {
        perror("dup");
        release_variables(shell->heads->environment);
        free(shell->heads);
        free(shell->fds);
        return (0);
    }
    return (1);
}

/*
 * Function: set_man_path
 * ----------------------
 * Appends custom 42sh manual page to the MANPATH environment variable
 *
 * - shell: shell's structure
 */
static void set_man_path(shell_t *shell)
{
    char *concatenate = NULL;
    char *buffer = NULL;

    buffer = getcwd(buffer, 0);
    if (buffer) {
        concatenate = calloc(strlen(buffer) + 8, sizeof(char));
    }
    if (!concatenate) {
        perror("malloc");
        free(buffer);
        return;
    }
    strcat(concatenate, buffer);
    strcat(concatenate, "/man/:");
    append_variable(&shell->heads->environment, "MANPATH", concatenate);
    free(buffer);
    free(concatenate);
}

/*
 * Function: set_shell_level
 * -------------------------
 * Sets current shell's level
 *
 * - shell: shell's structure
 */
static void set_shell_level(shell_t *shell)
{
    variable_t *shell_level = get_variable(shell->heads->environment, "SHLVL");
    char *buffer = NULL;
    int level = 0;

    if (!shell_level) {
        set_variable(&shell->heads->environment, "SHLVL", "0");
    } else {
        level = atoi(shell_level->value) + 1;
        buffer = my_itoa(level);
        set_variable(&shell->heads->environment, "SHLVL", buffer);
        free(buffer);
    }
}

/*
 * Function: set_default_aliases
 * -----------------------------
 * Sets shell's default aliases
 *
 * - shell: shell's structure
 */
static void set_default_aliases(shell_t *shell)
{
    set_variable(&shell->heads->aliases, "ls", "ls --color=auto");
    set_variable(&shell->heads->aliases, "grep", "grep --color=auto");
}

/*
 * Function: set_shell_data
 * ------------------------
 * Sets shell's default data
 *
 * - shell: shell's structure
 */
static void set_shell_data(shell_t *shell)
{
    set_man_path(shell);
    set_shell_level(shell);
    set_default_aliases(shell);
    shell->environment = convert_environment(shell->heads->environment);
    shell->ast = NULL;
    shell->last_argument = strdup("");
    shell->status = 0;
}

/*
 * Function: initialize_shell
 * --------------------------
 * Initializes shell's structure
 *
 * - shell: shell's structure
 *
 * Returns: 0 on errors, 1 otherwise
 */
int initialize_shell(shell_t *shell)
{
    if (!set_shell_head_nodes(shell)) {
        return (0);
    }
    if (!set_shell_standard_fds(shell)) {
        return (0);
    }
    if (signal(SIGINT, &signal_handler) == SIG_ERR
        || signal(SIGWINCH, &signal_handler) == SIG_ERR) {
        perror("signal");
        return (0);
    }
    set_shell_data(shell);
    return (1);
}
