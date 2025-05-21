/*
** EPITECH PROJECT, 2024
** lib/my/my_vdprintf_basics.c
** File description:
** Handles %n, %%, %c, %s %d and %i specifiers used by my_Xprintf.
*/

#include "my.h"

int print_wrote_chars(const char *restrict format, int fd, int *i, int *wrote)
{
    char *str = NULL;

    if (!format[*i + 1])
        return true;
    if (format[*i] == '%' && format[*i + 1] == 'n') {
        str = my_itoa(*wrote);
        if (!str)
            return true;
        *wrote += write(fd, str, my_strlen(str));
        free(str);
        *i += 1;
        return true;
    }
    return false;
}

int print_percentage(int fd, va_list *va)
{
    (void) va;
    return write(fd, "%", 1);
}

int print_char(int fd, va_list *va)
{
    char c = va_arg(*va, int);

    return write(fd, &c, 1);
}

int print_str(int fd, va_list *va)
{
    char *str = va_arg(*va, char *);
    unsigned int len = str ? my_strlen(str) : 6;

    return write(fd, str ? str : "(null)", len);
}

int print_int(int fd, va_list *va)
{
    int wrote = 0;
    char *str = my_itoa(va_arg(*va, int));

    if (!str)
        return write(fd, str ? str : "(malloc error)", 14);
    wrote = write(fd, str, my_strlen(str));
    free(str);
    return wrote;
}
