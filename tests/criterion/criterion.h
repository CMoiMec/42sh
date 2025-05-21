/*
** EPITECH PROJECT, 2024
** tests/criterion/criterion.h
** File description:
** Defines criterion's library path
** Author: @lszsrd
*/

#pragma once

#ifdef __APPLE__
    #include </opt/homebrew/include/criterion/criterion.h>
    #include </opt/homebrew/include/criterion/redirect.h>
    #define SEGFAULT_BINARY "./tests/binaries/darwin/segfault"
    #define WRONG_EXEC_BINARY "./tests/binaries/unix/segfault"
#else
    #include <criterion/criterion.h>
    #include <criterion/redirect.h>
    #define SEGFAULT_BINARY "./tests/binaries/unix/segfault"
    #define WRONG_EXEC_BINARY "./tests/binaries/darwin/segfault"
#endif

// Used for wait() prototype
#include <sys/wait.h>

#include "my.h"
#include "shell.h"
#include "builtin.h"
#include "execution.h"
