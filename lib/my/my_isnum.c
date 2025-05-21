/*
** EPITECH PROJECT, 2024
** lib/my/my_isnum.c
** File description:
** Returns true if given character is numeric, otherwise returns false.
*/

#include "my.h"

int my_isnum(char c)
{
    return c >= '0' && c <= '9';
}
