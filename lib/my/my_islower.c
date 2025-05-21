/*
** EPITECH PROJECT, 2024
** lib/my/my_islower.c
** File description:
** Returns true if given character is lowercase, otherwise returns false.
*/

#include "my.h"

int my_islower(char c)
{
    return c >= 'a' && c <= 'z';
}
