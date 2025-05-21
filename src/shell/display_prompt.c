/*
** EPITECH PROJECT, 2024
** src/shell/display_prompt.c
** File description:
** Displays prompt
** Author: @lszsrd
*/

// Used for passwd structure
#include <pwd.h>
// Used for getcwd() and getuid() prototypes
#include <unistd.h>
// Used for strncmp(), strlen() and strdup() prototypes
#include <string.h>
// Used for malloc() and free() prototypes
#include <stdlib.h>

#include "shell.h"

/*
 * Function: transform_active_dir
 * ------------------------------
 * Transforms current active directory to custom format if it is a branch of
 *  user's home directory
 *
 * - current_dir: actual current directory
 * - home_dir: environment's HOME value
 *
 * Returns: transformed actived directory or base current directory if no match
 */
char *transform_active_dir(char *current_dir, char *home_dir)
{
    char *active_dir = NULL;
    int current_dir_length = (current_dir) ? strlen(current_dir) : 0;
    int home_length = strlen(home_dir);

    if (!current_dir || strncmp(current_dir, home_dir, home_length)) {
        return (current_dir);
    }
    active_dir = malloc(sizeof(char) * (current_dir_length - home_length + 2));
    if (!active_dir) {
        return (current_dir);
    }
    for (int i = 0; i <= (current_dir_length - home_length); i++) {
        active_dir[i] = (i == 0) ? '~' : current_dir[home_length + i - 1];
    }
    active_dir[current_dir_length - home_length + 1] = 0;
    free(current_dir);
    return (active_dir);
}

/*
 * Function: display_prompt
 * ------------------------
 * Displays customized prompt with last exit status, user, machine and current
 *  working directory
 *
 * - shell: shell's structure
 */
void display_prompt(shell_t *shell)
{
    variable_t *home_var = get_variable(shell->heads->environment, "HOME");
    struct passwd *user = getpwuid(getuid());
    char *current_directory = NULL;
    char *host = malloc(sizeof(char) * 255);

    if (!host) {
        printf("%% ");
        return;
    }
    if (gethostname(host, 255) == -1) {
        free(host);
        host = strdup("42sh");
    }
    current_directory = (!home_var) ? getcwd(current_directory, 0)
        : transform_active_dir(getcwd(current_directory, 0), home_var->value);
    printf("\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[0m %% ",
        user->pw_name, host, current_directory);
    free(host);
    free(current_directory);
}
