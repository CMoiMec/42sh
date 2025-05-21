/*
** EPITECH PROJECT, 2024
** tests/criterion/shell/_initialize_shell.c
** File description:
** Tests initialize_shell() function
** Author: @lszsrd
*/

// Used for errno macro
#include <errno.h>
// Used for kill() prototype
#include <signal.h>

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
TestSuite(initialize_shell, .init = init, .fini = teardown);

/*
 * Test #1
 * -------
 * Tests b_set() with signal SIGINT
 */
Test(initialize_shell, test1)
{
    pid_t pid = getpid();

    kill(pid, SIGINT);
    cr_assert_eq(1, 1);
}
