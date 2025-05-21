/*
** EPITECH PROJECT, 2024
** src/variables/get_variable.c
** File description:
** Retrieves a variable from a variable_t linked list
** Author: @lszsrd
*/

// Used for strcmp() prototype
#include <string.h>

#include "variables.h"

/*
 * Function: get_variable
 * ----------------------
 * Retrieves a variable from a variable_t linked list
 *
 * head: variable_t's head
 * name: variable's name
 *
 * Returns: matching environment's linked list node, NULL otherwise
 */
variable_t *get_variable(variable_t *head, const char *name)
{
    if (!name) {
        return (NULL);
    }
    while (head) {
        if (!strcmp(head->name, name)) {
            return (head);
        }
        head = head->next;
    }
    return (NULL);
}
