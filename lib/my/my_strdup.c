/*
** EPITECH PROJECT, 2023
** lib/my/my_strdup.c
** File description:
** Duplicates a given string and returns an allocated copy.
*/

#include "my.h"

char *my_strdup(char const *src)
{
    int length = my_strlen(src);
    char *str = malloc(sizeof(char) * (length + 1));

    if (!str) {
        return (NULL);
    }
    my_memset(str, 0, length + 1);
    return (my_strcpy(str, src));
}
