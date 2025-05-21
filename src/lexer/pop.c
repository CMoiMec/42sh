/*
** EPITECH PROJECT, 2024
** src/parser/pop.c
** File description:
** Pops current token from lexer's stream
** Author: @lszsrd
*/

// Used for strlen() prototype
#include <string.h>

#include "lexer.h"

/*
 * Variable: parentheses
 * ---------------------
 * Looks up for parentheses string array variable definition from 'peek.c' file
 */
extern char *parentheses[];

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
 * Function: pop
 * -------------
 * Moves lexer's stream current index by the size of the current token
 *
 * TODO: Rewrite this function with peek() function, as we
 *  later will peek tokens by words instead of characters. That means that we
 *  will pop future token's length and no characters by characters anymore
 *
 * NOTE: This function has weak attribute which means, if rewrote, we won't
 *  have to delete this function and can save it if something goes wrong
 *
 * - stream: lexer's stream
 */
void pop(char **stream)
{
    token_t token = peek(*stream);

    if (token == PARENTHESE) {
        (*stream) += 1;
        return;
    }
    if (token == OPERATOR) {
        (*stream) += strlen(operators[get_operator_type(*stream)]);
        return;
    }
    if (token == REDIRECT) {
        (*stream) += strlen(redirects[get_redirect_type(*stream)]);
        return;
    }
    (*stream)++;
}
