/*
** EPITECH PROJECT, 2024
** lib/my/my_isupper.c
** File description:
** Returns true if given character is uppercase, otherwise returns false.
*/

#include "my.h"

int my_isupper(char c)
{
    return c >= 'A' && c <= 'Z' ? 1 : 0;
}
