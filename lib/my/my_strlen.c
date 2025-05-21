/*
** EPITECH PROJECT, 2023
** lib/my/my_strlen.c
** File description:
** Returns the length of the given string.
*/

int my_strlen(char const *str)
{
    int a = 0;

    for (; str[a]; a++);
    return a;
}
