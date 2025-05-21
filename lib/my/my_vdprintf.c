/*
** EPITECH PROJECT, 2024
** lib/my/my_vdprintf_basics.c
** File description:
** Primal call of the my_Xprintf functions.
*/

#include "my.h"
#include "my_vdprintf.h"

static int (*functions[24]) (int fd, va_list *va) = {
    print_int, print_int, print_octal, print_decimal,
    print_hexa_lower, print_hexa_upper, print_int,
    print_octal, print_decimal, print_scientific_lower, print_scientific_upper,
    print_double, print_double, not_supported, not_supported,
    not_supported, not_supported, not_supported, print_char,
    not_supported, print_str, print_pointer, print_percentage
};

int my_vdprintf(int fd, const char *restrict format, va_list *va)
{
    int wrote = 0;
    int var = 0;
    int l = 1;

    for (int i = 0; format[i]; i++) {
        wrote += format[i] != '%' ? write(fd, &format[i], 1) : 0;
        if (format[i] != '%' || print_wrote_chars(format, fd, &i, &wrote))
            continue;
        var = 0;
        for (l = 1; format[i + l] && !my_strchr(SPECIFIER, format[i + l]); l++)
            var = !my_strchr(FLAGS, format[i + l]) ||
            !my_strchr(MODIFIERS, format[i + l]) ? 1 : var;
        l *= var ? -1 : 1;
        if (l < 0)
            continue;
        for (var = 0; SPECIFIER[var] != format[i + l]; var++);
        wrote += functions[var] (fd, va);
        i += l < 0 ? l * -1 : l;
    }
    return wrote;
}

int my_printf(const char *restrict format, ...)
{
    int wrote = 0;
    va_list va;

    va_start(va, format);
    wrote = my_vdprintf(1, format, &va);
    va_end(va);
    return wrote;
}

int my_dprintf(int fd, const char *restrict format, ...)
{
    int wrote = 0;
    va_list va;

    va_start(va, format);
    wrote = my_vdprintf(fd, format, &va);
    va_end(va);
    return wrote;
}

int my_fprintf(FILE *stream, const char *restrict format, ...)
{
    int wrote = 0;
    va_list va;

    va_start(va, format);
    if (!stream || write(MY_FILENO(stream), "", 0) == -1)
        return -1;
    wrote = my_vdprintf(MY_FILENO(stream), format, &va);
    va_end(va);
    return wrote;
}
