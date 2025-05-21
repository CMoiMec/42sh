/*
** EPITECH PROJECT, 2024
** tests/criterion/execution/builtins/_setenv.c
** File description:
** Tests b_setenv() function
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
TestSuite(b_setenv, .init = init, .fini = teardown);

/*
 * Test #1
 * -------
 * Tests b_setenv() with no shell (pointless)
 */
Test(b_setenv, test1, .disabled = true)
{
    cr_assert_eq(b_setenv(NULL, NULL), 0);
}

/*
 * Test #2
 * -------
 * Tests b_setenv() with no arguments (parser checks that argv isn't NULL)
 */
Test(b_setenv, test2, .disabled = true)
{
    cr_assert_eq(b_setenv(&shell, NULL), 0);
}

/*
 * Test #3
 * -------
 * Tests b_setenv() with invalid argument: number first: checking error message
 */
Test(b_setenv, test3)
{
    argv = my_str_to_word_array("setenv 1A", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#3: malloc error: %s\n", strerror(errno));
    }
    b_setenv(&shell, (const char **) argv);
    cr_assert_stderr_eq_str("setenv: Variable name must begin with a letter.\n");
}

/*
 * Test #4
 * -------
 * Tests b_setenv() with invalid argument: number first: checking return value
 */
Test(b_setenv, test4)
{
    argv = my_str_to_word_array("setenv 1A", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#4: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_setenv(&shell, (const char **) argv), 1);
}

/*
 * Test #5
 * -------
 * Tests b_setenv() with invalid to many arguments: checking error message
 */
Test(b_setenv, test5)
{
    argv = my_str_to_word_array("setenv arg1 arg2 arg3", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#5: malloc error: %s\n", strerror(errno));
    }
    b_setenv(&shell, (const char **) argv);
    cr_assert_stderr_eq_str("setenv: Too many arguments.\n");
}

/*
 * Test #6
 * -------
 * Tests b_setenv() with invalid to many arguments: checking return value
 */
Test(b_setenv, test6)
{
    argv = my_str_to_word_array("setenv arg1 arg2 arg3", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#6: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_setenv(&shell, (const char **) argv), 1);
}

/*
 * Test #7
 * -------
 * Tests b_setenv() with invalid argument: invalid char: checking error message
 */
Test(b_setenv, test7)
{
    argv = my_str_to_word_array("setenv NAME=", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#7: malloc error: %s\n", strerror(errno));
    }
    b_setenv(&shell, (const char **) argv);
    cr_assert_stderr_eq_str("setenv: Variable name must contain alphanumeric characters.\n");
}

/*
 * Test #8
 * -------
 * Tests b_setenv() with invalid argument: invalid char: checking error message
 */
Test(b_setenv, test8)
{
    argv = my_str_to_word_array("setenv NAME/", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#8: malloc error: %s\n", strerror(errno));
    }
    b_setenv(&shell, (const char **) argv);
    cr_assert_stderr_eq_str("setenv: Variable name must contain alphanumeric characters.\n");
}

/*
 * Test #9
 * -------
 * Tests b_setenv() with invalid argument: invalid char: checking return value
 */
Test(b_setenv, test9)
{
    argv = my_str_to_word_array("setenv NAME-", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#9: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_setenv(&shell, (const char **) argv), 1);
}

/*
 * Test #10
 * --------
 * Tests b_setenv() with valid (1/2) argument
 */
Test(b_setenv, test10)
{
    argv = my_str_to_word_array("setenv NAME", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#10: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_setenv(&shell, (const char **) argv), 0);
}

/*
 * Test #11
 * --------
 * Tests b_setenv() with valid (2/2) arguments
 */
Test(b_setenv, test11)
{
    argv = my_str_to_word_array("setenv NAME value", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#11: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_setenv(&shell, (const char **) argv), 0);
}

/*
 * Test #12
 * --------
 * Tests b_setenv() with valid variable name (special case)
 */
Test(b_setenv, test12)
{
    argv = my_str_to_word_array("setenv a.", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#12: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_setenv(&shell, (const char **) argv), 0);
}
