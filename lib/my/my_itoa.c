/*
** EPITECH PROJECT, 2024
** lib/my/my_itoa.c
** File description:
** Converts and returns an int to a string.
*/

#include "my.h"

char *my_itoa(int nb)
{
    char *str = NULL;
    int abs_nb = ABS(nb);
    int size = nb < 0 ? 1 : 0;

    for (int i = abs_nb; i > 9; i /= 10)
        size++;
    str = malloc(sizeof(char) * (size + 1) + 1);
    if (!str)
        return NULL;
    for (int i = size; i >= 0; i--) {
        str[i] = 48 + abs_nb % 10;
        abs_nb /= 10;
    }
    str[0] = nb < 0 ? '-' : str[0];
    str[size + 1] = 0;
    return str;
}
