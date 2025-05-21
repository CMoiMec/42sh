/*
** EPITECH PROJECT, 2024
** lib/my/my_strlowcase.c
** File description:
** Returns a lowercase version of the given string.
*/

#include "my.h"

char *my_strlowcase(char *str)
{
    for (int a = 0; str[a] != 0; a++)
        str[a] += my_isupper(str[a]) ? 32 : 0;
    return str;
}
