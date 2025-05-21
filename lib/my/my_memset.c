/*
** EPITECH PROJECT, 2024
** lib/my/my_memset.c
** File description:
** Initializes len bytes of c of b.
*/

#include "my.h"

/* Initializes len bytes of c of b.*/
void *my_memset(void *b, int c, size_t len)
{
    char *ptr = b;

    for (size_t i = 0; i < len; i++)
        ptr[i] = c;
    b = ptr;
    return b;
}
