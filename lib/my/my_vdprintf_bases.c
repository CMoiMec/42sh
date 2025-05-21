/*
** EPITECH PROJECT, 2024
** lib/my/my_vdprintf_bases.c
** File description:
** Handles %x, %X, %o, %O, %u, %U and %p specifiers used by my_Xprintf.
*/

#include "my.h"

static int print_base(int fd, unsigned long long nb, short base, bool lower)
{
    int wrote = 0;
    char *converted_string;
    unsigned short len = 0;

    for (long long copy = nb; copy / base > 0; len++)
        copy /= base;
    converted_string = malloc(sizeof(char) * (len + 2));
    if (!converted_string)
        return write(fd, "(malloc error)", 14);
    for (int i = len; i >= 0; i--) {
        if (nb % base > 9)
            converted_string[i] = nb % base + (lower ? 87 : 55);
        else
            converted_string[i] = nb % base + 48;
        nb /= base;
    }
    converted_string[len + 1] = 0;
    wrote = write(fd, converted_string, my_strlen(converted_string));
    free(converted_string);
    return wrote;
}

int print_hexa_lower(int fd, va_list *va)
{
    return print_base(fd, va_arg(*va, int), 16, true);
}

int print_hexa_upper(int fd, va_list *va)
{
    return print_base(fd, va_arg(*va, int), 16, false);
}

int print_octal(int fd, va_list *va)
{
    return print_base(fd, va_arg(*va, int), 8, false);
}

int print_decimal(int fd, va_list *va)
{
    return print_base(fd, va_arg(*va, int), 10, false);
}

int print_pointer(int fd, va_list *va)
{
    void *pt = va_arg(*va, void *);

    if (!pt)
        return write(fd, "(nil)", 5);
    return write(fd, "0x", 2) + print_base(fd, (unsigned long long) pt, 16, 1);
}
