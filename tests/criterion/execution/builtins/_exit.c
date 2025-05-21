/*
** EPITECH PROJECT, 2024
** tests/criterion/execution/builtins/_exit.c
** File description:
** Tests b_exit() function
** Author: @lszsrd
*/

// Used for errno macro
#include <errno.h>

#include "../../criterion.h"

/*
 * Variable: shell
 * ---------------
 * Defines shell's structure
 */
static shell_t shell;

/*
 * Variable: argv
 * --------------
 * Defines arguments
 */
static char **argv;

/*
 * Function: init
 * --------------
 * Initializes shell's structure at test's start and redirects
 *  standard input and standard output
 */
static void init(void)
{
    initialize_shell(&shell);
    cr_redirect_stdout();
    cr_redirect_stderr();
}

/*
 * Function: teardown
 * ------------------
 * Releases shell's structure at test's exit
 */
static void teardown(void)
{
    cleanup_shell(&shell);
    my_strfreev(argv);
}

/*
 * TestSuite
 * ---------
 * Defines .init and .fini functions of this test suite
 */
TestSuite(b_exit, .init = init, .fini = teardown);

/*
 * Test #1
 * -------
 * Tests b_exit() with invalid argument: checking error message
 */
Test(b_exit, test1)
{
    argv = my_str_to_word_array("exit invalid", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#1: malloc error: %s\n", strerror(errno));
    }
    b_exit(&shell, (const char **) argv);
    cr_assert_stderr_eq_str("exit: Expression Syntax.\n");
}

/*
 * Test #2
 * -------
 * Tests b_exit() with negative argument
 */
Test(b_exit, test2)
{
    pid_t child = 0;

    argv = my_str_to_word_array("exit -42", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#2: malloc error: %s\n", strerror(errno));
    }
    child = fork();
    if (child == -1) {
        cr_assert_eq(1, 0, "KO: T#2: fork error: %s\n", strerror(errno));
    }
    if (child == 0) {
        b_exit(&shell, (const char **) argv);
    } else {
        wait(&child);
    }
    cr_assert_eq(WEXITSTATUS(child), 214);
}

/*
 * Test #3
 * -------
 * Tests b_exit() with positive argument
 */
Test(b_exit, test3)
{
    pid_t child = 0;

    argv = my_str_to_word_array("exit 42", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#3: malloc error: %s\n", strerror(errno));
    }
    child = fork();
    if (child == -1) {
        cr_assert_eq(1, 0, "KO: T#3: fork error: %s\n", strerror(errno));
    }
    if (child == 0) {
        b_exit(&shell, (const char **) argv);
    } else {
        wait(&child);
    }
    cr_assert_eq(WEXITSTATUS(child), 42);
}

/*
 * Test #4
 * -------
 * Tests b_exit() with last shell's exit status
 */
Test(b_exit, test4)
{
    pid_t child = 0;

    shell.status = 84;
    argv = my_str_to_word_array("exit", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#4: malloc error: %s\n", strerror(errno));
    }
    child = fork();
    if (child == -1) {
        cr_assert_eq(1, 0, "KO: T#4: fork error: %s\n", strerror(errno));
    }
    if (child == 0) {
        b_exit(&shell, (const char **) argv);
    } else {
        wait(&child);
    }
    cr_assert_eq(WEXITSTATUS(child), 84);
}

/*
 * Test #5
 * -------
 * Tests b_exit() with -0
 */
Test(b_exit, test5)
{
    pid_t child = 0;

    shell.status = 84;
    argv = my_str_to_word_array("exit -0", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#5: malloc error: %s\n", strerror(errno));
    }
    child = fork();
    if (child == -1) {
        cr_assert_eq(1, 0, "KO: T#5: fork error: %s\n", strerror(errno));
    }
    if (child == 0) {
        b_exit(&shell, (const char **) argv);
    } else {
        wait(&child);
    }
    cr_assert_eq(WEXITSTATUS(child), 0);
}

/*
 * Test #6
 * -------
 * Tests b_exit() with 0
 */
Test(b_exit, test6)
{
    pid_t child = 0;

    shell.status = 84;
    argv = my_str_to_word_array("exit 0", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#6: malloc error: %s\n", strerror(errno));
    }
    child = fork();
    if (child == -1) {
        cr_assert_eq(1, 0, "KO: T#6: fork error: %s\n", strerror(errno));
    }
    if (child == 0) {
        b_exit(&shell, (const char **) argv);
    } else {
        wait(&child);
    }
    cr_assert_eq(WEXITSTATUS(child), 0);
}
