/*
** EPITECH PROJECT, 2024
** src/globbins/my_pars.c
** File description:
** Funciton to manipulate string
** Author: @cmoimec
*/

#include "globbins.h"

/*
 * Function: my_array_len
 * ----------------------
 * Return the number of string in a array
 *
 * - array: a array of string
 */
int my_array_len(char **array)
{
    int i = 0;

    if (array == NULL) {
        return -1;
    }
    for (; array[i]; i ++);
    return i;
}
