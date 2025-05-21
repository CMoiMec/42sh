/*
** EPITECH PROJECT, 2024
** lib/my/my.h
** File description:
** Handles functions prototypes and maccros used by my library.
*/

#pragma once

/* Defines precision of the my_dtoa function.*/
#define DTOA_PRECISION (int) 6

/* Includes used for system calls and/or libc's prototypes.*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

/* Include my_Xprintf family prototypes.*/
#include "my_vdprintf.h"

/* Functions to check a string's characters */
int my_strlen(char const *);
int my_getnbr(char const *);
char *my_strchr(const char *, const char);
int my_str_isnum(char const *str);
int my_str_isalnum(char const *str);
// and its dependencies
int my_isalpha(char);
int my_islower(char);
int my_isupper(char);
int my_isnum(char);
int my_isalnum(char);
/* Functions to act on a string */
char *my_strupcase(char *);
char *my_strlowcase(char *str);
char *my_strdup(char const *src);
char *my_strcpy(char *, char const *);
char *my_strcat(char *, char const *);
int my_strcmp(char const *, char const *);
int my_strncmp(char const *s1, char const *s2, size_t n);
char *my_revstr(char *);
char **my_str_to_word_array(char const *str, const char *sep);
void my_strfreev(char **array);
void my_swap(void *a, void *b);
void *my_memset(void *b, int c, size_t len);
char *my_word_array_to_str(char **stwa);
/* Functions to get a string */
char *my_itoa(int number);
char *my_dtoa(double number);
