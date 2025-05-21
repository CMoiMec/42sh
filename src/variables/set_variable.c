/*
** EPITECH PROJECT, 2024
** src/variables/set_variable.c
** File description:
** Sets a variable of a variable_t linked list
** Author: @lszsrd
*/

// Used for malloc() prototype
#include <stdlib.h>
// Used for strdup() prototype
#include <string.h>
// Used for perror() prototype
#include <stdio.h>

#include "variables.h"

/*
 * Function: add_variable
 * ----------------------
 * Adds a variable to the end of a variable_t linked list
 *
 * head: variable_t's head
 * name: variable's name
 * value: variable's content
 *
 * Returns: 1 on success, 0 otherwise
 */
static int add_variable(variable_t **head, const char *name, const char *value)
{
    variable_t *variable = *head;

    for (; variable && variable->next; variable = variable->next);
    if (!variable) {
        variable = malloc(sizeof(variable_t));
    } else {
        variable->next = malloc(sizeof(variable_t));
        variable = variable->next;
    }
    if (!variable) {
        perror("malloc");
        return (0);
    }
    variable->name = strdup(name);
    variable->value = strdup(value);
    variable->next = NULL;
    if (!*head) {
        *head = variable;
    }
    return (1);
}

/*
 * Function: update_variable
 * -------------------------
 * Updates a variable of a variable_t linked list
 *
 * variable: variable
 * value: new variable's content
 *
 * Returns: 1 on success, 0 otherwise
 */
static int update_variable(variable_t *variable, const char *value)
{
    free(variable->value);
    variable->value = strdup(value);
    if (!variable->value) {
        return (0);
    }
    return (1);
}

/*
 * Function: set_variable
 * ----------------------
 * Sets a variable of a variable_t linked list
 * Note: On environment change, user should recreate it
 *
 * head: variable_t's head
 * name: variable's name
 * value: variable's content
 *
 * Returns: 1 on success, 0 otherwise
 */
int set_variable(variable_t **head, const char *name, const char *value)
{
    variable_t *variable = get_variable(*head, name);

    if (!name) {
        return (0);
    }
    if (!value) {
        value = "";
    }
    if (!variable) {
        return (add_variable(head, name, value));
    } else {
        return (update_variable(variable, value));
    }
}
