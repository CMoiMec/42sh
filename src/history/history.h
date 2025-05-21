/*
** EPITECH PROJECT, 2024
** src/shell.h
** File description:
** Defines shell's structure and prototypes
** Author: @lszsrd
*/

#pragma once

typedef struct ast_s ast_t;

/*
 * Structure: history_t
 * --------------------
 * Defines shell's history
 */
typedef struct history_s {
    char *command;
    char *timestamp;
    struct history_s *next;
    struct history_s *prev;
} history_t;

/*
 * Prototypes definition
 */

void add_to_history(history_t **head, char *command);
char *dump_ast(ast_t *ast, const char *stream);

// Internal prototype used by dump_ast() function

void expand_ast_operands(ast_t *ast, char **command);
