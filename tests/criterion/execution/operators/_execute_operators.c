/*
** EPITECH PROJECT, 2024
** tests/criterion/execution/operators/_execute_operators.c
** File description:
** Tests execute_operators() function
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
TestSuite(execute_operators, .init = init, .fini = teardown);

/*
 * Test #1
 * -------
 * Tests execute_operators(): testing with AND operator (invalid left operand)
 */
Test(execute_operators, test1)
{
    stream = strdup("ls non_existing_file && ls");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#1: malloc error: %s\n", strerror(errno));
    }
    expand_ast(&shell, shell.ast);
    cr_assert_eq(shell.status, 2);
}

/*
 * Test #2
 * -------
 * Tests execute_operators(): testing with AND operator (valid left and right operand)
 */
Test(execute_operators, test2)
{
    stream = strdup("ls && ls");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#2: malloc error: %s\n", strerror(errno));
    }
    expand_ast(&shell, shell.ast);
    cr_assert_eq(shell.status, 0);
}

/*
 * Test #3
 * -------
 * Tests execute_operators(): testing with OR operator (invalid left operand)
 */
Test(execute_operators, test3)
{
    stream = strdup("ls non_existing_file || ls");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#3: malloc error: %s\n", strerror(errno));
    }
    expand_ast(&shell, shell.ast);
    cr_assert_eq(shell.status, 0);
}

/*
 * Test #4
 * -------
 * Tests execute_operators(): testing with OR operator (valid operands)
 */
Test(execute_operators, test4)
{
    stream = strdup("ls || ls");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#4: malloc error: %s\n", strerror(errno));
    }
    expand_ast(&shell, shell.ast);
    cr_assert_eq(shell.status, 0);
}

/*
 * Test #5
 * -------
 * Tests execute_operators(): testing with ;
 */
Test(execute_operators, test5)
{
    stream = strdup("ls ; ls");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#5: malloc error: %s\n", strerror(errno));
    }
    expand_ast(&shell, shell.ast);
    cr_assert_eq(shell.status, 0);
}

/*
 * Test #6
 * -------
 * Tests execute_operators(): testing with AND operator (invalid middle operand)
 */
Test(execute_operators, test6)
{
    stream = strdup("ls && ls non_existing_file && ls");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#6: malloc error: %s\n", strerror(errno));
    }
    expand_ast(&shell, shell.ast);
    cr_assert_eq(shell.status, 2);
}

/*
 * Test #7
 * -------
 * Tests execute_operators(): testing with OR operator (invalid right operand)
 */
Test(execute_operators, test7)
{
    stream = strdup("ls || echo KO");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#7: malloc error: %s\n", strerror(errno));
    }
    expand_ast(&shell, shell.ast);
    cr_assert_stdout_neq_str("KO");
}
