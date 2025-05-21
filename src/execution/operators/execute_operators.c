/*
** EPITECH PROJECT, 2024
** src/execution/operators/execute_operators.c
** File description:
** Expands and executes operators of the given AST
** Author: @lszsrd
*/

#include "execution.h"

/*
 * Function: execute_operators
 * ---------------------------
 * Expands and executes operators of the given AST
 *
 * - shell: shell's structure
 * - ast: an abstract syntax tree containing command to execute
 */
void execute_operators(shell_t *shell, const ast_t *ast)
{
    expand_ast(shell, ast->operator.left);
    if (ast->operator.type == AND && shell->status != 0) {
        return;
    }
    if (ast->operator.type == OR && shell->status == 0) {
        return;
    }
    expand_ast(shell, ast->operator.right);
}
