/*
** EPITECH PROJECT, 2024
** src/variables/variables.h
** File description:
** Defines environment's/local variables' structure and prototypes
** Author: @lszsrd
*/

#pragma once

/*
 * Structure: environment_t
 * ------------------------
 * Stores variable name, value and its next pointer in the linked list
 */
typedef struct variable_s {
    char *name;
    char *value;
    struct variable_s *next;
} variable_t;

/*
 * Prototypes definition
 */

variable_t *create_environment(char **env);
char **convert_environment(variable_t *head);

variable_t *get_variable(variable_t *head, const char *name);
int set_variable(variable_t **head, const char *name, const char *value);
int unset_variable(variable_t **head, const char *name);
int append_variable(variable_t **head, const char *name, const char *value);
