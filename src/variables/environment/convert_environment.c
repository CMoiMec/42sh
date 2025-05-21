/*
** EPITECH PROJECT, 2024
** src/variables/environment/convert_environment.c
** File description:
** Converts environment's linked list to a strings array
** Author: @lszsrd
*/

#include "my.h"
#include "variables.h"

/*
 * Function: get_environment_nodes_count
 * -------------------------------------
 * Gets total environment's node count
 *
 * head: environment's head
 *
 * Returns: environment's nodes count
 */
static int get_environment_nodes_count(variable_t *head)
{
    int environment_nodes_count = 0;

    while (head) {
        environment_nodes_count++;
        head = head->next;
    }
    return (environment_nodes_count);
}

/*
 * Function: set_environment_line
 * ------------------------------
 * Sets current environment's line value
 *
 * line: environment's line
 * head: current environment's node
 *
 * Returns: 1 if succeed, 0 otherwise
 */
static int set_environment_line(char **line, variable_t *head)
{
    int line_length = strlen(head->name) + strlen(head->value) + 2;

    *line = malloc(sizeof(char) * (line_length));
    if (!*line) {
        perror("malloc");
        return (0);
    }
    memset(*line, 0, line_length);
    strcpy(*line, head->name);
    strcat(*line, "=");
    strcat(*line, head->value);
    return (1);
}

/*
 * Function: convert_environment
 * -----------------------------
 * Converts environment's linked list to a strings array
 *
 * head: environment's head
 *
 * Returns: environment, as a string array
 */
char **convert_environment(variable_t *head)
{
    char **environment = NULL;
    int environment_nodes_count = get_environment_nodes_count(head);

    if (!environment_nodes_count) {
        return (NULL);
    }
    environment = malloc(sizeof(char *) * (environment_nodes_count + 1));
    if (!environment) {
        return (NULL);
    }
    for (int i = 0; head; i++) {
        if (!set_environment_line(&environment[i], head)) {
            environment[i] = NULL;
            my_strfreev(environment);
            return (NULL);
        }
        head = head->next;
    }
    environment[environment_nodes_count] = NULL;
    return (environment);
}
