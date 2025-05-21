/*
** EPITECH PROJECT, 2024
** src/history/dump_ast.c
** File description:
** Dumps given AST to an allocated string
** Author: @lszsrd
*/

#include "my.h"
#include "parser.h"
#include "history.h"

/*
 * Variable: operators
 * -------------------
 * Looks up for operators string array variable definition from 'peek.c' file
 */
extern char *operators[];

/*
 * Variable: redirects
 * -------------------
 * Looks up for redirects string array variable definition from 'peek.c' file
 */
extern char *redirects[];

/*
 * Function: concatenate_operators
 * -------------------------------
 * Concatenates AST operator to the resulting string
 *
 * - ast: current AST node
 * - command: resulting string
 */
static void concatenate_operators(ast_t *ast, char **command)
{
    expand_ast_operands(ast->operator.left, command);
    if ((*command)[strlen(*command) - 1] != ' ') {
        strcat(*command, " ");
    }
    strcat(*command, operators[ast->operator.type]);
    if (ast->operator.right) {
        strcat(*command, " ");
    }
    expand_ast_operands(ast->operator.right, command);
}

/*
 * Function: concatenate_redirects
 * -------------------------------
 * Concatenates AST redirect to the resulting string
 *
 * - ast: current AST node
 * - command: resulting string
 */
static void concatenate_redirects(ast_t *ast, char **command)
{
    expand_ast_operands(ast->redirect.left, command);
    if ((*command)[strlen(*command) - 1] != ' ') {
        strcat(*command, " ");
    }
    strcat(*command, redirects[ast->redirect.type]);
    if (ast->redirect.right) {
        strcat(*command, " ");
    }
    expand_ast_operands(ast->redirect.right, command);
}

/*
 * Function: concatenate_commands
 * ------------------------------
 * Concatenates a command to the resulting string
 *
 * - ast: current AST node
 * - command: resulting string
 */
static void concatenate_commands(ast_t *ast, char **command)
{
    char *buffer = NULL;

    buffer = my_word_array_to_str(ast->command.argv);
    strcat(*command, (buffer) ? buffer : "");
    free(buffer);
}

/*
 * Function: expand_ast_operands
 * -----------------------------
 * Expands AST's nodes
 *
 * - ast: current AST node
 * - command: resulting string
 */
void expand_ast_operands(ast_t *ast, char **command)
{
    if (ast) {
        switch (ast->type) {
            case OPERATOR:
                concatenate_operators(ast, command);
                break;
            case REDIRECT:
                concatenate_redirects(ast, command);
                break;
            default:
                concatenate_commands(ast, command);
        }
    }
}

/*
 * Function: dump_ast
 * ------------------
 * Dumps given AST to an allocated string
 *
 * - ast: ast to dump
 *
 * Returns: converted AST to an allocated string or NULL on empty commands
 */
char *dump_ast(ast_t *ast, const char *stream)
{
    char *command = NULL;

    if (!ast) {
        return (NULL);
    }
    command = calloc(2 * (strlen(stream) + 1), sizeof(char));
    if (!command) {
        perror("calloc");
        return (NULL);
    }
    expand_ast_operands(ast, &command);
    if (!command[0]) {
        free(command);
        return (NULL);
    }
    if (command[strlen(command) - 1] == ' ') {
        command[strlen(command) - 1] = '\0';
    }
    return (command);
}
