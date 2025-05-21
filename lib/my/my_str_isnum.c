/*
** EPITECH PROJECT, 2024
** lib/my/my_str_is_num.c
** File description:
** Returns true if given string is numeric, otherwise returns false.
*/

#include "my.h"

int my_str_isnum(char const *str)
{
    for (int a = 0; str[a] != '\0'; a++)
        if (my_isnum(str[a]) == 0)
            return 0;
    return 1;
}
