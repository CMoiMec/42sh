/*
** EPITECH PROJECT, 2024
** lib/my/my_strupcase.c
** File description:
** Returns an uppercase version of the given string.
*/

#include "my.h"

char *my_strupcase(char *str)
{
    for (int a = 0; str[a] != 0; a++)
        str[a] -= my_islower(str[a]) ? 32 : 0;
    return str;
}
