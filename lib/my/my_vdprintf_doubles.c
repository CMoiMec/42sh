/*
** EPITECH PROJECT, 2024
** lib/my/my_vdprintf_basics.c
** File description:
** Handles %f, %e, %E specifiers used by my_Xprintf.
*/

#include "my.h"
#include "my_vdprintf.h"

static int get_exponent(double *number)
{
    int exponent = 0;
    int safety = 0;

    for (double copy = *number; copy > 9; copy /= 10)
        exponent++;
    exponent = !(int) *number ? 0 : exponent;
    for (; (int) *number == 0 && safety < SCIENTIFIC_SAFETY; *number *= 10) {
        exponent--;
        safety++;
    }
    return safety != SCIENTIFIC_SAFETY ? exponent : 0;
}

static void set_exponent(char *str, double number, int exponent, int is_neg)
{
    str[7 + is_neg] += (int) (number * 10) % 10 >= 5 ? 1 : 0;
    str[9 + is_neg] = exponent < 0 ? '-' : '+';
    str[10 + is_neg] = ABS(exponent) / 10 + 48;
    str[11 + is_neg] = ABS(exponent) % 10 + 48;
    str[12 + is_neg] = 0;
}

static char *get_scientific(double number, int lower)
{
    int is_neg = (1 / number) < 0.0;
    int exponent = get_exponent(&number);
    char *str = malloc(13 + is_neg);

    if (!str)
        return NULL;
    number = is_neg ? -number : number;
    for (; number > 9; number /= 10);
    str[0] = is_neg ? '-' : 48 + (int) number;
    str[1] = is_neg ? 48 + (int) number : '.';
    number = is_neg ? number * 10 : number;
    str[2] = is_neg ? '.' : + (int) number;
    number = is_neg ? number / 10 : number;
    for (int i = 2 + is_neg; i <= 7 + is_neg; i++) {
        number *= 10;
        str[i] = 48 + (int) number % 10;
    }
    str[8 + is_neg] = lower ? 'e' : 'E';
    set_exponent(str, number, exponent, is_neg);
    return str;
}

int print_double(int fd, va_list *va)
{
    char *str = my_dtoa(va_arg(*va, double));
    int wrote = 0;

    if (!str)
        return write(fd, "(malloc error)", 14);
    wrote = write(fd, str, my_strlen(str));
    free(str);
    return wrote;
}

int print_scientific_lower(int fd, va_list *va)
{
    char *str = get_scientific(va_arg(*va, double), true);
    int wrote = 0;

    if (!str)
        return write(fd, "(malloc error)", 14);
    wrote = write(fd, str, my_strlen(str));
    free(str);
    return wrote;
}

int print_scientific_upper(int fd, va_list *va)
{
    char *str = get_scientific(va_arg(*va, double), false);
    int wrote = 0;

    if (!str)
        return write(fd, "(malloc error)", 14);
    wrote = write(fd, str, my_strlen(str));
    free(str);
    return wrote;
}

int not_supported(int fd, va_list *va)
{
    char str[] = "[NOT SUPPORTED]";

    (void) va;
    return write(fd, str, my_strlen(str));
}
