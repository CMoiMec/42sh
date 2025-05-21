/*
** EPITECH PROJECT, 2024
** tests/criterion/execution/builtins/_set.c
** File description:
** Tests b_set() function
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
TestSuite(b_set, .init = init, .fini = teardown);

/*
 * Test #1
 * -------
 * Tests b_set() with no shell (pointless)
 */
Test(b_set, test1, .disabled = true)
{
    cr_assert_eq(b_set(NULL, NULL), 0);
}

/*
 * Test #2
 * -------
 * Tests b_set() with no arguments (parser checks that argv isn't NULL)
 */
Test(b_set, test2, .disabled = true)
{
    cr_assert_eq(b_set(&shell, NULL), 0);
}

/*
 * Test #3
 * -------
 * Tests b_set() with invalid argument: number first: checking error message
 */
Test(b_set, test3)
{
    argv = my_str_to_word_array("set 1A", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#3: malloc error: %s\n", strerror(errno));
    }
    b_set(&shell, (const char **) argv);
    cr_assert_stderr_eq_str("set: Variable name must begin with a letter.\n");
}

/*
 * Test #4
 * -------
 * Tests b_set() with intended correct usage
 */
Test(b_set, test4)
{
    argv = my_str_to_word_array("set NAME = value", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#4: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_set(&shell, (const char **) argv), 0);
}

/*
 * Test #5
 * -------
 * Tests b_set() with multiple correct usage
 */
Test(b_set, test5)
{
    argv = my_str_to_word_array("set NAME = value NAME2 = value2", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#5: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_set(&shell, (const char **) argv), 0);
}

/*
 * Test #6
 * -------
 * Tests b_set() with no value
 */
Test(b_set, test6)
{
    argv = my_str_to_word_array("set NAME", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#6: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_set(&shell, (const char **) argv), 0);
}

/*
 * Test #7
 * -------
 * Tests b_set() with intended correct usage (forces print)
 */
Test(b_set, test7)
{
    argv = my_str_to_word_array("set NAME", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#7-0: malloc error: %s\n", strerror(errno));
    }
    b_set(&shell, (const char **) argv);
    my_strfreev(argv);
    argv = my_str_to_word_array("set", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#7-1: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_set(&shell, (const char **) argv), 0);
}

/*
 * Test #8
 * -------
 * Tests b_set() with intended correct usage (special case)
 */
Test(b_set, test8)
{
    argv = my_str_to_word_array("set NAME NAME2 =", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#8-0: malloc error: %s\n", strerror(errno));
    }
    b_set(&shell, (const char **) argv);
    my_strfreev(argv);
    argv = my_str_to_word_array("set", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#8-1: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_set(&shell, (const char **) argv), 0);
}
