/*
** EPITECH PROJECT, 2024
** tests/criterion/execution/builtins/_env.c
** File description:
** Tests b_env() function
** Author: @lszsrd
*/

#include "../../criterion.h"

/*
 * Variable: environ
 * -----------------
 * Imports environment
 */
extern char **environ;

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
TestSuite(b_env, .init = init, .fini = teardown);

/*
 * Test #1
 * -------
 * Tests b_env() with no shell (pointless)
 */
Test(b_env, test1, .disabled = true)
{
    cr_assert_eq(b_env(NULL, NULL), 0);
}

/*
 * Test #2
 * -------
 * Tests b_env() with initialized shell: checking return value
 */
Test(b_env, test2)
{
    cr_assert_eq(b_env(&shell, NULL), 0);
}
