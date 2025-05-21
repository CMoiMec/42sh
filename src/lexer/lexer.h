/*
** EPITECH PROJECT, 2024
** src/lexer/lexer.h
** File description:
** Defines lexer's enumerations, structures and prototypes
** Author: @lszsrd
*/

#pragma once

// Used for INT_MAX macro
#include <limits.h>

/*
 * Macro: PARENTHESES
 * ------------------
 * Defines parentheses symbols
 */

#define PARENTHESES "(", ")"

/*
 * Macro: OPERATORS
 * ----------------
 * Defines operators symbols
 */
#define OPERATORS "&&", "||"

/*
 * Macro: REDIRECTS
 * ----------------
 * Defines redirects symbols
 */
#define REDIRECTS ">>", ">", "|", "<<", "<"

/*
 * Macro: UNDEFINED_TYPE
 * ---------------------
 * Defines undefined type value.
 * It MUST be more than operator_t or redirect_t maximum values
 */
#define UNDEFINED_TYPE INT_MAX

/*
 * Enumeration: parenthese_t
 * -------------------------
 * Enumerates parenthese types
 */
typedef enum parenthese_e {
    LEFT_PARENTHESE, RIGHT_PARENTHESE
} parenthese_t;

/*
 * Enumeration: operator_t
 * -----------------------
 * Enumerates operators types
 */
typedef enum operator_e {
    SEMICOLON = 0, AND, OR
} operator_t;

/*
 * Enumeration: redirect_t
 * -----------------------
 * Enumerates redirects types
 */
typedef enum redirect_e {
    STREAM_APPEND, STREAM, PIPE, HERE_DOCUMENT, INPUT
} redirect_t;

/*
 * Enumeration: token_t
 * --------------------
 * Enumerates tokens types
 */
typedef enum token_e {
    CHARACTER, COMMAND, REDIRECT, OPERATOR, PARENTHESE, EOL
} token_t;

/*
 * Prototypes definition
 */

parenthese_t get_parenthese_type(const char *stream);
operator_t get_operator_type(const char *stream);
redirect_t get_redirect_type(const char *stream);

token_t peek(const char *stream);
void pop(char **stream);
