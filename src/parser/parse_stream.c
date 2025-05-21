/*
** EPITECH PROJECT, 2024
** src/parser/parse_stream.c
** File description:
** Parses buffer to a valid abstract syntax tree
** Author: @lszsrd
*/

#include "my.h"
#include "shell.h"

/*
 * Function: release_ast
 * ---------------------
 * Releases AST's allocated memory
 *
 * - ast: AST to release
 */
void release_ast(ast_t *ast)
{
    if (ast) {
        switch (ast->type) {
            case OPERATOR:
                release_ast(ast->operator.left);
                release_ast(ast->operator.right);
                break;
            case REDIRECT:
                release_ast(ast->redirect.left);
                release_ast(ast->redirect.right);
                break;
            default:
                free(ast->command.binary);
                my_strfreev(ast->command.argv);
        }
        free(ast);
    }
}

/*
 * Function: operators_inspector
 * ------------------------------------
 * Checks if the given operator AST is valid
 *
 * - ast: current operator AST to inspect
 *
 * Returns: 1 if redirect is valid, 0 otherwise
 */
static int operators_inspector(const ast_t *ast)
{
    if (ast->operator.left == NULL && ast->operator.type == OR) {
        dprintf(2, NULL_COMMAND);
        return (0);
    }
    if (ast->operator.right == NULL && ast->operator.type != SEMICOLON) {
        dprintf(2, NULL_COMMAND);
        return (0);
    }
    return (1);
}

/*
 * Function: redirects_inspector
 * -----------------------------
 * Checks if the given redirect AST is valid
 *
 * - ast: current redirect AST to inspect
 * - inputs: total input redirects in the global AST
 * - outputs: total output redirects in the global AST
 *
 * Returns: 1 if redirect is valid, 0 otherwise
 */
static int redirects_inspector(const ast_t *ast, int *inputs, int *outputs)
{
    if (ast->redirect.type == INPUT || ast->redirect.type == HERE_DOCUMENT) {
        *inputs += 1;
    } else {
        *outputs += 1;
    }
    if (!ast->redirect.left || !ast->redirect.right) {
        dprintf(2, !ast->redirect.right && ast->redirect.type != PIPE ?
            NULL_REDIRECT : NULL_COMMAND);
        return (0);
    }
    if (ast->redirect.type == PIPE && ast->redirect.right->type == REDIRECT)
        *outputs -= 1;
    if (*inputs > 1 || *outputs > 1 || (ast->redirect.type == PIPE
        && ast->redirect.right->type == REDIRECT
        && (ast->redirect.right->redirect.type == HERE_DOCUMENT
        || ast->redirect.right->redirect.type == INPUT))) {
        dprintf(2, *outputs > 1 ? AMBIGUOUS_OUTPUT : AMBIGUOUS_INPUT);
        return (0);
    }
    return (1);
}

/*
 * Function: ast_inspector
 * -----------------------
 * Checks if the given AST is valid
 *
 * - ast: current redirect AST to inspect
 * - inputs: total input redirects in the global AST
 * - outputs: total output redirects in the global AST
 *
 * Returns: 1 if AST is valid, 0 otherwise
 */
static int ast_inspector(const ast_t *ast, int inputs, int outputs)
{
    if (!ast) {
        return (1);
    }
    switch (ast->type) {
        case OPERATOR:
            if (!ast_inspector(ast->operator.left, inputs, outputs)
                || !operators_inspector(ast)) {
                return (0);
            }
            return (ast_inspector(ast->operator.right, inputs, outputs));
        case REDIRECT:
            if (!redirects_inspector(ast, &inputs, &outputs)) {
                return (0);
            }
            return (ast_inspector(ast->redirect.right, inputs, outputs));
        default:
            return (1);
    }
    return (1);
}

/*
 * Function: parse_stream
 * ----------------------
 * Parses given buffer into one abstract syntax tree
 *
 * - buffer: characters array to parse
 *
 * Returns: created AST, it may be NULL if subroutines detected errors
 */
ast_t *parse_stream(shell_t *shell, char *buffer)
{
    const char *stream = buffer;
    ast_t *ast = NULL;

    if (!stream) {
        return (NULL);
    }
    ast = parse_operators(&stream);
    add_to_history(&shell->heads->history, dump_ast(ast, buffer));
    free(buffer);
    if (!ast) {
        shell->status = 0;
        return (NULL);
    }
    if (!ast_inspector(ast, 0, 0)) {
        shell->status = 1;
        release_ast(ast);
        ast = NULL;
    }
    return (ast);
}
