/*
** EPITECH PROJECT, 2024
** lib/my/my_isalnum.c
** File description:
** Returns true if given character is alpha-numeric, otherwise returns false.
*/

#include "my.h"

int my_isalnum(char c)
{
    return my_isalpha(c) > 0 || my_isnum(c) > 0;
}
