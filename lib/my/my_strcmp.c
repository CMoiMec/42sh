/*
** EPITECH PROJECT, 2023
** /lib/my/my_strcmp.c
** File description:
** Compares the given strings and returns the ASCII difference.
*/

int my_strcmp(char const *s1, char const *s2)
{
    for (int a = 0; (s1[a] != 0 || s2[a] != 0); a++) {
        if (s1[a] != s2[a])
            return (s1[a] - s2[a]);
    }
    return 0;
}
