/*
** EPITECH PROJECT, 2024
** src/execution/expander.c
** File description:
** Expands AST and call appropriate module given the current AST type
** Author: @lszsrd
*/

#include "execution.h"

/*
 * Function: expand_ast
 * --------------------
 * Expands AST and call appropriate module given the current AST type
 *
 * - shell: shell's structure
 * - ast: shell's AST to expand
 */
void expand_ast(shell_t *shell, const ast_t *ast)
{
    if (!ast) {
        return;
    }
    switch (ast->type) {
        case OPERATOR:
            execute_operators(shell, ast);
            break;
        case REDIRECT:
            execute_redirects(shell, ast);
            break;
        case COMMAND:
            execute_command(shell, ast, 1);
            break;
        default:
            break;
    }
}
