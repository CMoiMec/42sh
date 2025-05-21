/*
** EPITECH PROJECT, 2024
** lib/my/my_word_array_to_str.c
** File description:
** Checks if given command is valid
** Author: @lszsrd
*/

#include "my.h"

/*
 * Function: my_word_array_to_str
 * ------------------------------
 * Transforms a strings array to an allocated array
 *
 * Returns: an allocated buffer on success, NULL otherwise
 */

char *my_word_array_to_str(char **stwa)
{
    char *string = NULL;
    int total_length = 0;
    int argc = 0;

    if (!stwa)
        return (NULL);
    for (; stwa[argc]; argc++)
        total_length += my_strlen(stwa[argc]);
    string = malloc(sizeof(char) * (total_length + argc + 1));
    if (!string)
        return (NULL);
    my_memset(string, 0, total_length + argc + 1);
    for (int i = 0; stwa[i]; i++) {
        my_strcat(string, stwa[i]);
        if (stwa[i + 1])
            my_strcat(string, " ");
    }
    return (string);
}
