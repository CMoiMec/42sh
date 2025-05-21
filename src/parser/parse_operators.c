/*
** EPITECH PROJECT, 2024
** src/parser/parse_operators.c
** File description:
** Parses commands and/or redirects into operators AST
** Author: @lszsrd
*/

// Used for malloc() prototype
#include <stdlib.h>

#include "parser.h"

/*
 * Function: parse_operators
 * -------------------------
 * Merges commands and/or redirects into an operator AST
 *
 * - stream: lexer's stream
 *
 * Returns: created operator AST or redirect AST on errors
 */
ast_t *parse_operators(const char **stream)
{
    ast_t *redirect = parse_redirects(stream);
    ast_t *ast = NULL;

    if (peek(*stream) == OPERATOR) {
        ast = malloc(sizeof(ast_t));
        if (!ast) {
            return (redirect);
        }
        ast->type = OPERATOR;
        ast->operator.type = get_operator_type(*stream);
        ast->operator.left = redirect;
        pop((char **) stream);
        ast->operator.right = parse_operators(stream);
        return (ast);
    }
    return (redirect);
}
