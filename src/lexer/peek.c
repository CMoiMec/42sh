/*
** EPITECH PROJECT, 2024
** src/lexer/peek.c
** File description:
** Peeks token from lexer's stream
** Author: @lszsrd
*/

// Used for strncmp() and strlen() prototypes
#include <string.h>

#include "lexer.h"

/*
 * Variable: parentheses
 * ---------------------
 * Converts PARENTHESES symbols to a strings array (see lexer.h)
 */
const char *parentheses[] = { PARENTHESES, NULL };

/*
 * Variable: operators
 * -------------------
 * Converts OPERATORS symbols to a strings array (see lexer.h)
 */
const char *operators[] = { ";", OPERATORS, NULL };

/*
 * Variable: redirects
 * -------------------
 * Converts REDIRECTS symbols to a strings array (see lexer.h)
 */
const char *redirects[] = { REDIRECTS, NULL };

/*
 * Function: get_parenthese_type
 * -----------------------------
 * Gets parenthese type (see lexer.h)
 *
 * - stream: lexer's stream
 *
 * Returns: parenthese's ID or UNDEFINED_TYPE if no match was found
 */
__attribute__((unused)) parenthese_t get_parenthese_type(const char *stream)
{
    for (parenthese_t i = 0; parentheses[i]; i++) {
        if (!strncmp(stream, parentheses[i], strlen(parentheses[i]))) {
            return (i);
        }
    }
    return (UNDEFINED_TYPE);
}

/*
 * Function: get_operator_type
 * ---------------------------
 * Gets operator type (see lexer.h)
 *
 * - stream: lexer's stream
 *
 * Returns: operator's ID or UNDEFINED_TYPE if no match was found
 */
operator_t get_operator_type(const char *stream)
{
    for (operator_t i = 0; operators[i]; i++) {
        if (!strncmp(stream, operators[i], strlen(operators[i]))) {
            return (i);
        }
    }
    return (UNDEFINED_TYPE);
}

/*
 * Function: get_redirect_type
 * ---------------------------
 * Gets redirect type (see lexer.h)
 *
 * - stream: lexer's stream
 *
 * Returns: redirect's ID or UNDEFINED_TYPE if no match was found
 */
redirect_t get_redirect_type(const char *stream)
{
    for (redirect_t i = 0; redirects[i]; i++) {
        if (!strncmp(stream, redirects[i], strlen(redirects[i]))) {
            return (i);
        }
    }
    return (UNDEFINED_TYPE);
}

/*
 * Function: peek
 * --------------
 * Retrieves lexer's stream current token type
 *
 * TODO: Uses a token structure storing special type and token length avoiding
 *  parse_commands() function to call peek() at each characters
 *
 * - stream: lexer's stream
 *
 * Returns: lexer's stream's current token type
 */
token_t peek(const char *stream)
{
    if (!stream[0] || !strncmp(stream, "\n", 1)) {
        return (EOL);
    }
    if (get_operator_type(stream) != UNDEFINED_TYPE) {
        return (OPERATOR);
    }
    if (get_redirect_type(stream) != UNDEFINED_TYPE) {
        return (REDIRECT);
    }
    return (CHARACTER);
}
