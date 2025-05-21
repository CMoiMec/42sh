/*
** EPITECH PROJECT, 2024
** lib/my/my_getnbr.c
** File description:
** Converts and returns a string to an int.
*/

#include "my.h"

int my_getnbr(char const *str)
{
    long res = 0;
    bool neg = false;

    for (int i = 0; str[i] != 0; i++) {
        neg = (str[i] == '-') ? !neg : neg;
        if (my_isnum(str[i]))
            res = (res * 10) + str[i] - 48;
        if (res != 0 && !my_isnum(str[i]))
            break;
    }
    return (neg) ? res * -1 : res;
}
