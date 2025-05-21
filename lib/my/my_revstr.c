/*
** EPITECH PROJECT, 2024
** lib/my/my_revstr.c
** File description:
** Reverses the given string and returns it.
*/

#include "my.h"

char *my_revstr(char *str)
{
    int str_len = my_strlen(str);
    char str_rev[str_len + 1];

    for (int a = 1; a <= str_len; a++)
        str_rev[a - 1] = str[str_len - a];
    for (int a = 0; a < str_len; a++)
        str[a] = str_rev[a];
    return str;
}
