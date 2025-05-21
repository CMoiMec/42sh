/*
** EPITECH PROJECT, 2024
** lib/my/my_swap.c
** File description:
** Swaps given pointers.
*/

void my_swap(void *a, void *b)
{
    void *temp = b;

    b = a;
    a = temp;
}
