/*
** EPITECH PROJECT, 2024
** minishell/dependencies/my_strfreev.c
** File description:
** Releases allocated memory used on a char **.
*/

#include "my.h"

/* Free allocated char char**.*/
void my_strfreev(char **array)
{
    if (!array)
        return;
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}
