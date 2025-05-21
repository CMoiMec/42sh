/*
** EPITECH PROJECT, 2023
** /lib/my/my_strncmp.c
** File description:
** Compares up to n characters of the given strings and returns
** the ASCII difference.
*/

#include "my.h"

int my_strncmp(char const *s1, char const *s2, size_t n)
{
    for (size_t a = 0; (s1[a] != 0 || s2[a] != 0) && a < n; a++) {
        if (s1[a] != s2[a])
            return (s1[a] - s2[a]);
    }
    return 0;
}
