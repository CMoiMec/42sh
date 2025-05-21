/*
** EPITECH PROJECT, 2024
** src/variables/environment/create_environment.c
** File description:
** Creates environment's linked list
** Author: @lszsrd
*/

// Used for malloc() prototype
#include <stdlib.h>
// Used for strtok() and strdup() prototypes
#include <string.h>
// Used for perror() prototype
#include <stdio.h>

#include "variables.h"

/*
 * Function: set_variable_content
 * ------------------------------
 * Fills variable's name, value and next pointer
 *
 * env_variable: current environment node
 * line: current environment line
 */
static void set_variable_content(variable_t *env_variable, const char *line)
{
    char *buffer = NULL;

    buffer = strtok((char *) line, "=");
    env_variable->name = strdup((buffer) ? buffer : "");
    buffer = strtok(NULL, "\n");
    if (!buffer) {
        env_variable->value = strdup("");
    } else {
        env_variable->value = strdup(buffer);
    }
    env_variable->next = NULL;
}

/*
 * Function: create_environment
 * ----------------------------
 * Creates environment's linked list
 *
 * env: shell's environment
 *
 * Returns: head of the environment linked list
 */
variable_t *create_environment(char **env)
{
    variable_t *head = NULL;
    variable_t *env_variable = NULL;
    variable_t *prev = NULL;

    for (int i = 0; env && env[i]; i++) {
        env_variable = malloc(sizeof(variable_t));
        if (!env_variable) {
            perror("malloc");
            continue;
        }
        set_variable_content(env_variable, env[i]);
        if (i == 0) {
            head = env_variable;
        } else {
            prev->next = env_variable;
            prev = env_variable;
        }
        prev = env_variable;
    }
    return (head);
}
