/*
** EPITECH PROJECT, 2024
** src/parser/parse_commands.c
** File description:
** Parses characters into commands AST
** Author: @lszsrd
*/

// Used for malloc() and free() prototypes
#include <stdlib.h>
// Used for memset() and strdup() prototypes
#include <string.h>

#include "parser.h"

/*
 * Function: parse_commands
 * ------------------------
 * Merges characters to a commands by peeking/popping tokens from lexer
 *
 * - stream: lexer's stream
 *
 * Returns: created command AST or NULL on errors
 */
ast_t *parse_commands(const char **stream)
{
    ast_t *ast = malloc(sizeof(ast_t));
    char command[strlen(*stream) + 1];

    memset(command, 0, sizeof(command));
    for (int i = 0; peek(*stream) == CHARACTER; i++) {
        command[i] = (*stream)[0];
        pop((char **) stream);
    }
    if (!ast) {
        return (NULL);
    }
    ast->type = COMMAND;
    ast->command.argv = my_str_to_word_array_escaper(command, SEPARATORS);
    if (!ast->command.argv) {
        free(ast);
        return (NULL);
    }
    ast->command.binary = strdup(ast->command.argv[0]);
    return (ast);
}
