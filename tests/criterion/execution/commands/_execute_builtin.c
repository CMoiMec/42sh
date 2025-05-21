/*
** EPITECH PROJECT, 2024
** tests/criterion/execution/commands/_execute_builtin.c
** File description:
** Tests execute_builtin() function
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
 * Variable: stream
 * ----------------
 * Defines lexer's stream
 */
static char *stream;

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
TestSuite(execute_builtin, .init = init, .fini = teardown);

/*
 * Test #1
 * -------
 * Tests execute_builtins(): non existing builtin
 */
Test(execute_builtin, test1)
{
    stream = strdup("this_is_not_a_builtin");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#1: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(execute_builtin(&shell, shell.ast), 0);
}

/*
 * Test #2
 * -------
 * Tests execute_builtins(): cd
 */
Test(execute_builtin, test2)
{
    stream = strdup("cd");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#2: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(execute_builtin(&shell, shell.ast), 1);
}

/*
 * Test #3
 * -------
 * Tests execute_builtins(): env
 */
Test(execute_builtin, test3)
{
    stream = strdup("env");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#3: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(execute_builtin(&shell, shell.ast), 1);
}

/*
 * Test #4
 * -------
 * Tests execute_builtins(): exit
 */
Test(execute_builtin, test4)
{
    stream = strdup("exit");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#4: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(execute_builtin(&shell, shell.ast), 1);
}

/*
 * Test #5
 * -------
 * Tests execute_builtins(): setenv
 */
Test(execute_builtin, test5)
{
    stream = strdup("setenv");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#5: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(execute_builtin(&shell, shell.ast), 1);
}

/*
 * Test #6
 * -------
 * Tests execute_builtins(): unsetenv
 */
Test(execute_builtin, test6)
{
    stream = strdup("unsetenv");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#6: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(execute_builtin(&shell, shell.ast), 1);
}

/*
 * Test #7
 * -------
 * Tests execute_builtins(): set
 */
Test(execute_builtin, test7)
{
    stream = strdup("set");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#7: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(execute_builtin(&shell, shell.ast), 1);
}

/*
 * Test #8
 * -------
 * Tests execute_builtins(): unset
 */
Test(execute_builtin, test8)
{
    stream = strdup("unset");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#8: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(execute_builtin(&shell, shell.ast), 1);
}
