/*
** EPITECH PROJECT, 2024
** src/parser/parse_redirects.c
** File description:
** Parses commands into redirects AST
** Author: @lszsrd
*/

// Used for malloc() prototype
#include <stdlib.h>

#include "parser.h"

/*
 * Function: parse_redirects
 * -------------------------
 * Merges commands into a redirects AST
 *
 * - stream: lexer's stream
 *
 * Returns: created redirect AST, command AST or NULL on errors
 */
ast_t *parse_redirects(const char **stream)
{
    ast_t *command = parse_commands(stream);
    ast_t *ast = NULL;

    if (peek(*stream) == REDIRECT) {
        ast = malloc(sizeof(ast_t));
        if (!ast) {
            return (command);
        }
        ast->type = REDIRECT;
        ast->redirect.type = get_redirect_type(*stream);
        ast->redirect.left = command;
        pop((char **) stream);
        ast->redirect.right = parse_redirects(stream);
        return (ast);
    }
    return (command);
}
