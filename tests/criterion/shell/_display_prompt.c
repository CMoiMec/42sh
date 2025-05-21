/*
** EPITECH PROJECT, 2024
** tests/criterion/shell/_display_prompt.c
** File description:
** Tests display_prompt() function
** Author: @lszsrd
*/

// Used for errno macro
#include <errno.h>

#include "../criterion.h"

/*
 * Variable: shell
 * ---------------
 * Defines shell's structure
 */
static shell_t shell;

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
}

/*
 * TestSuite
 * ---------
 * Defines .init and .fini functions of this test suite
 */
TestSuite(display_prompt, .init = init, .fini = teardown);

/*
 * Test #1
 * -------
 * Tests display_prompt()
 */
Test(display_prompt, test1)
{
    display_prompt(&shell);
    cr_assert_eq(1, 1);
}
