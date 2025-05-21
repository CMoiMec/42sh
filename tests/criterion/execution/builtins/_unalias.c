/*
** EPITECH PROJECT, 2024
** tests/criterion/execution/builtins/_unalias.c
** File description:
** Tests b_unalias() function
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
TestSuite(b_unalias, .init = init, .fini = teardown);

/*
 * Test #1
 * -------
 * Tests b_unalias() test not enougth arguments: return value
 */
Test(b_unalias, test1)
{
    argv = my_str_to_word_array("unalias", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#1: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_unalias(&shell, (const char **) argv), 1);
}

/*
 * Test #2
 * -------
 * Tests b_unalias() test not enougth arguments: error message
 */
Test(b_unalias, test2)
{
    argv = my_str_to_word_array("unalias", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#2: malloc error: %s\n", strerror(errno));
    }
    b_unalias(&shell, (const char **) argv);
    cr_assert_stderr_eq_str("unalias: Too few arguments.\n");
}

/*
 * Test #3
 * -------
 * Tests b_unalias() test unsets an alias
 */
Test(b_unalias, test3)
{
    argv = my_str_to_word_array("unalias ls", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#3: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_unalias(&shell, (const char **) argv), 0);
}
