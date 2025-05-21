/*
** EPITECH PROJECT, 2024
** lib/my/my_vdprintf.h
** File description:
** Handles functions prototypes and maccros used by my_Xprintf functions.
*/

#pragma once

/* Include for va_args macros.*/
#include <stdarg.h>

/* Retrieves file descriptor from a STREAM structure.*/
#ifdef __APPLE__
    #define MY_FILENO(stream) stream->_file
#else
    #define MY_FILENO(stream) stream->_fileno
#endif

/* Returns absolute value from an integer.*/
#define ABS(x) (x < 0 ? x * -1 : x)

/* Defines my_Xprintf family format specifiers, flags and modifiers.*/
#define SPECIFIER "diouxXDOUeEfFgGaACcSsp%"
#define FLAGS "#0- +.*"
#define MODIFIERS "hlqLjzZt"

/* Defines max number of 0 to check after a comma on scientif functions.*/
#define SCIENTIFIC_SAFETY (int) 16

/* Defines my_Xprintf family internals prototypes.*/
int print_wrote_chars(const char *restrict format, int fd, int *i, int *wrote);
int not_supported(int fd, va_list *va);
int print_char(int fd, va_list *va);
int print_str(int fd, va_list *va);
int print_int(int fd, va_list *va);
int print_percentage(int fd, va_list *va);
int print_hexa_lower(int fd, va_list *va);
int print_hexa_upper(int fd, va_list *va);
int print_octal(int fd, va_list *va);
int print_decimal(int fd, va_list *va);
int print_pointer(int fd, va_list *va);
int print_double(int fd, va_list *va);
int print_scientific_lower(int fd, va_list *va);
int print_scientific_upper(int fd, va_list *va);
/* Defines my_Xprintf family's prototypes.*/
int my_vdprintf(int fd, const char *restrict format, va_list *va);
int my_printf(const char *restrict, ...);
int my_dprintf(int fd, const char *restrict, ...);
int my_fprintf(FILE *stream, const char *restrict format, ...);
