/*
** EPITECH PROJECT, 2024
** lib/my/my_strcopy.c
** File description:
** Copies the sources string to the dest string and returns it.
*/

#include "my.h"

char *my_strcpy(char *dest, char const *src)
{
    for (unsigned int index = 0; src[index]; index++)
        dest[index] = src[index];
    return (dest);
}
