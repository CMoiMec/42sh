/*
** EPITECH PROJECT, 2024
** src/variables/unset_variable.c
** File description:
** Un-sets a variable from a variables_t linked list
** Author: @lszsrd
*/

// Used for free() prototype
#include <stdlib.h>

#include "variables.h"

/*
 * Function: unset_variable
 * ------------------------
 * Un-sets a variable from a variables_t linked list.
 * Note: On environment change, user should recreate it
 *
 * head: environment's head
 * name: variable's name
 *
 * Returns: 0
 */
int unset_variable(variable_t **head, const char *name)
{
    variable_t *variable = get_variable(*head, name);
    variable_t *prev = *head;

    if (!variable) {
        return (0);
    }
    for (; prev && prev->next != variable; prev = prev->next);
    if (variable != *head) {
        prev->next = variable->next;
    } else {
        *head = variable->next;
    }
    free(variable->name);
    free(variable->value);
    free(variable);
    return (0);
}
