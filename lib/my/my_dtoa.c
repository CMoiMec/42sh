/*
** EPITECH PROJECT, 2024
** lib/my/my_dtoa.c
** File description:
** Converts and retutns a double to a string.
*/

#include "my.h"

struct vars_t {
    char *str;
    int decimal_length;
    unsigned long long decimal;
    unsigned long long modulo;
};

static void initialize_struct(struct vars_t *vars, double number)
{
    int copy = number;

    vars->str = NULL;
    vars->decimal_length = number < 0 ? 2 : 1;
    vars->decimal = number < 0 ? -number : number;
    vars->modulo = 1;
    if (number < 0)
        copy *= -1;
    for (; copy > 9; copy /= 10) {
        vars->modulo *= 10;
        vars->decimal_length++;
    }
}

static void handle_integer_part(struct vars_t *vars, double number)
{
    for (int i = number < 0; i < vars->decimal_length; i++) {
        vars->str[i] = vars->decimal / vars->modulo + 48;
        vars->decimal -= (vars->decimal / vars->modulo) * vars->modulo;
        vars->modulo /= 10;
    }
    vars->str[0] = number < 0 ? '-' : vars->str[0];
    vars->str[vars->decimal_length] = '.';
}

char *my_dtoa(double number)
{
    struct vars_t vars;

    initialize_struct(&vars, number);
    vars.str = malloc(vars.decimal_length + DTOA_PRECISION + 2);
    if (!vars.str)
        return NULL;
    handle_integer_part(&vars, number);
    if (number < 0)
        number *= -1;
    vars.modulo = 10;
    for (int i = 1; i <= DTOA_PRECISION; i++) {
        vars.decimal = number * vars.modulo;
        vars.modulo *= 10;
    }
    for (int i = DTOA_PRECISION; i > 0; i--) {
        vars.str[vars.decimal_length + i] = vars.decimal % 10 + 48;
        vars.decimal /= 10;
    }
    vars.str[vars.decimal_length + DTOA_PRECISION + 1] = 0;
    return vars.str;
}
