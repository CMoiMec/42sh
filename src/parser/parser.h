/*
** EPITECH PROJECT, 2024
** src/parser/parser.h
** File description:
** Defines parser's AST and prototypes
** Author: @lszsrd
*/

#pragma once

#include "lexer.h"

/*
 * Macro: NULL_COMMAND
 * -------------------
 * Defines error message when operand of an operator is missing
 */
#define NULL_COMMAND "Invalid null command.\n"

/*
 * Macro: NULL_REDIRECT
 * --------------------
 * Defines error message when when operand of a redirect is missing
 */
#define NULL_REDIRECT "Missing name for redirect.\n"

/*
 * Macro: AMBIGUOUS_INPUT
 * ----------------------
 * Defines error message when there are multiple input redirects in place
 */
#define AMBIGUOUS_INPUT "Ambiguous input redirect.\n"

/*
 * Macro: AMBIGUOUS_OUTPUT
 * -----------------------
 * Defines error message when there are multiple output redirects in place
 */
#define AMBIGUOUS_OUTPUT "Ambiguous output redirect.\n"

/*
 * Macro: SEPARATORS
 * -----------------
 * Defines separators used by parse_commands()' argv parser
 */
#define SEPARATORS " \"'\t\n()"

/*
 * Structure: shell_t
 * ------------------
 * Redefinition of shell's structure prototype as we cannot include "shell.h"
 *  due to circular imports
 */
typedef struct shell_s shell_t;

/*
 * Structure: ast_t
 * ----------------
 * Defines parser's Abstract Syntax Tree (AST) backbone
 */
typedef struct ast_s {
    token_t type;
    union {
        struct {
            struct ast_s *left;
            struct ast_s *right;
            parenthese_t type;
        }
        parenthese;
        struct {
            struct ast_s *left;
            struct ast_s *right;
            operator_t type;
        }
        operator;
        struct {
            struct ast_s *left;
            struct ast_s *right;
            redirect_t type;
        }
        redirect;
        struct {
            char **argv;
            char *binary;
        } command;
    };
} ast_t;

/*
 * Prototypes definition
 */

void release_ast(ast_t *ast);

ast_t *parse_stream(shell_t *shell, char *stream);

ast_t *parse_operators(const char **stream);
ast_t *parse_redirects(const char **stream);
ast_t *parse_commands(const char **stream);

char **my_str_to_word_array_escaper(const char *str, const char *separators);
