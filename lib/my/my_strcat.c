/*
** EPITECH PROJECT, 2024
** lib/my/my_strcat.c
** File description:
** Concanates dest and source strings and returns the newly transformed dest.
*/

#include "my.h"

char *my_strcat(char *dest, char const *src)
{
    my_strcpy(&dest[my_strlen(dest)], src);
    return (dest);
}
