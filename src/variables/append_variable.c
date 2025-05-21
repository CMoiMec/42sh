/*
** EPITECH PROJECT, 2024
** src/variables/append_variable.c
** File description:
** Appends data to a variable
** Author: @lszsrd
*/

#include "my.h"
#include "variables.h"
#include <stdlib.h>
#include <string.h>

/*
 * Function: get_variable
 * ----------------------
 * Retrieves a variable from a variable_t linked list
 *
 * head: variable_t's head
 * name: variable's name
 * value: variable's value
 *
 * Returns: 0 on errors, bytes wrote otherwise
 */
int append_variable(variable_t **head, const char *name, const char *value)
{
    variable_t *node = *head;

    if (!name || !value) {
        return (0);
    }
    while (node && strcmp(node->name, name)) {
        node = node->next;
    }
    if (!node || strcmp(node->name, name)) {
        set_variable(head, name, value);
        return (0);
    }
    node->value = realloc(node->value, sizeof(char) * (strlen(node->value)
        + strlen(node->value) + 1));
    if (!node->value) {
        return (0);
    }
    strcat(node->value, value);
    return (strlen(node->value));
}
