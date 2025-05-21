/*
** EPITECH PROJECT, 2024
** lib/my/my_strchr.c
** File description:
** Searches and returns the first occurrence of the given character on the
** given string.
*/

#include "my.h"

char *my_strchr(const char *s, char c)
{
    for (int i = 0; s[i]; i++)
        if (s[i] == c)
            return (char *) &s[i];
    return NULL;
}
