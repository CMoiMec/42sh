/*
** EPITECH PROJECT, 2024
** lib/my/my_isalpha.c
** File description:
** Returns true if given character is alpha, otherwise returns false.
*/

#include "my.h"

int my_isalpha(char c)
{
    return my_islower(c) > 0 || my_isupper(c) > 0;
}
