/*
** EPITECH PROJECT, 2024
** tests/criterion/shell/_read_stream.c
** File description:
** Tests read_stream() function
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
TestSuite(read_stream, .init = init, .fini = teardown);

/*
 * Test #1
 * -------
 * Tests read_stream() with a given input
 */
Test(read_stream, test1)
{
    fprintf(stdin, "this is a command to read\n");
    cr_assert_neq(read_stream(&shell), NULL);
}

/*
 * Test #2
 * -------
 * Tests read_stream() exit message
 */
Test(read_stream, test2)
{
    fclose(stdin);
    read_stream(&shell);
    cr_assert_stdout_eq_str("exit\n");
}
