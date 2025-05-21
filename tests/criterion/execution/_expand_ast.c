/*
** EPITECH PROJECT, 2024
** tests/criterion/execution/_expand_ast.c
** File description:
** Tests expand_ast() function
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
TestSuite(expand_ast, .init = init, .fini = teardown);

/*
 * Test #1
 * -------
 * Tests expand_ast(): testing with a NULL AST
 */
Test(expand_ast, test1)
{
    stream = strdup("ls");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#1: malloc error: %s\n", strerror(errno));
    }
    expand_ast(&shell, NULL);
    cr_assert_eq(shell.status, 0);
}

/*
 * Test #2
 * -------
 * Tests expand_ast(): testing with a simple command
 */
Test(expand_ast, test2)
{
    stream = strdup("ls");
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
 * Tests expand_ast(): testing with a redirect
 */
Test(expand_ast, test3)
{
    stream = strdup("ls < non_existing_file_to_fail_this_test_on_purpose");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#3: malloc error: %s\n", strerror(errno));
    }
    expand_ast(&shell, shell.ast);
    cr_assert_eq(shell.status, 1);
}

/*
 * Test #4
 * -------
 * Tests expand_ast(): testing with an operator
 */
Test(expand_ast, test4)
{
    stream = strdup("ls || ls");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#4: malloc error: %s\n", strerror(errno));
    }
    expand_ast(&shell, shell.ast);
    cr_assert_eq(shell.status, 0);
}
