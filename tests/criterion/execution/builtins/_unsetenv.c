/*
** EPITECH PROJECT, 2024
** tests/criterion/execution/builtins/_unsetenv.c
** File description:
** Tests b_unsetenv() function
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
TestSuite(b_unsetenv, .init = init, .fini = teardown);

/*
 * Test #1
 * -------
 * Tests b_unsetenv() with no shell (pointless)
 */
Test(b_unsetenv, test1, .disabled = true)
{
    cr_assert_eq(b_unsetenv(NULL, NULL), 1);
}

/*
 * Test #2
 * -------
 * Tests b_unsetenv() with no arguments (parser checks that argv isn't NULL)
 */
Test(b_unsetenv, test2, .disabled = true)
{
    cr_assert_eq(b_unsetenv(&shell, NULL), 1);
}

/*
 * Test #3
 * -------
 * Tests b_unsetenv() with no arguments (empty)
 */
Test(b_unsetenv, test3)
{
    argv = my_str_to_word_array("unsetenv", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#3: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_unsetenv(&shell, (const char **) argv), 1);
}

/*
 * Test #4
 * -------
 * Tests b_unsetenv() with 3 arguments
 */
Test(b_unsetenv, test4)
{
    argv = my_str_to_word_array("unsetenv arg1 arg2 arg3", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#4: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_unsetenv(&shell, (const char **) argv), 0);

}

/*
 * Test #5
 * -------
 * Tests b_unsetenv() with no arguments: checking error message
 */
Test(b_unsetenv, test5)
{
    argv = my_str_to_word_array("unsetenv", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#5: malloc error: %s\n", strerror(errno));
    }
    b_unsetenv(&shell, (const char **) argv);
    cr_assert_stderr_eq_str("unsetenv: Too few arguments.\n");
}
