/*
** EPITECH PROJECT, 2024
** lib/my/my_str_is_alnum.c
** File description:
** Returns true if given string is alpha-numeric, otherwise returns false.
*/

#include "my.h"

int my_str_isalnum(char const *str)
{
    for (int a = 0; str[a] != '\0'; a++)
        if (my_isalnum(str[a]) > 0)
            return 0;
    return 1;
}
