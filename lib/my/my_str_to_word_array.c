/*
** EPITECH PROJECT, 2023
** /lib/my/my_str_to_word_array.c
** File description:
** Extracts words separated from given separators patern and returns
** an array of those strings.
*/

#include "my.h"

/* Re-wrote (again) a better version taking a given string as separators
 - 'wo' stands for words, which contains the number of real words in the string
 - 'l' stands for len, which is the length of the word
 - 'in' stands for index, it it the index in the string
*/
char **my_str_to_word_array(const char *s, const char *se)
{
    char **array = NULL;
    unsigned int wo = 0;
    unsigned int l = 0;
    unsigned int in = 0;

    for (int i = 0; s[i] != 0; i++)
        if (!my_strchr(se, s[i]))
            wo += my_strchr(se, s[i + 1]) || s[i + 1] == 0 ? 1 : 0;
    array = wo != 0 ? malloc(sizeof(char *) * (wo + 1)) : array;
    for (unsigned int i = 0; array != NULL && i < wo; i++) {
        for (in += l; my_strchr(se, s[in]); in++);
        for (l = 0; !my_strchr(se, s[in + l]) && s[in + l]; l++);
        array[i] = malloc(sizeof(char) * (l + 1));
        for (unsigned int j = 0; array[i] != NULL && j <= l; j++)
            array[i][j] = j != l ? s[in + j] : 0;
    }
    if (wo != 0)
        array[wo] = NULL;
    return array;
}
