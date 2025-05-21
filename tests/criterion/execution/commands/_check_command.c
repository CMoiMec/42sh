/*
** EPITECH PROJECT, 2024
** tests/criterion/execution/commands/_check_command.c
** File description:
** Tests check_command() function
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
TestSuite(check_command, .init = init, .fini = teardown);

/*
 * Test #1
 * -------
 * Tests check_command() with non existing local command: checking return value
 */
Test(check_command, test1)
{
    stream = strdup("./fake_binary");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#1: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(check_command(&shell, shell.ast), 0);
}

/*
 * Test #2
 * -------
 * Tests check_command() with non existing local command: checking error message
 */
Test(check_command, test2)
{
    stream = strdup("./fake_binary");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#2: malloc error: %s\n", strerror(errno));
    }
    check_command(&shell, shell.ast);
    cr_assert_stderr_eq_str("./fake_binary: Command not found.\n");
}

/*
 * Test #3
 * -------
 * Tests check_command() with a directory: checking return value
 */
Test(check_command, test3)
{
    stream = strdup("./src");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#3: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(check_command(&shell, shell.ast), 0);
}

/*
 * Test #4
 * -------
 * Tests check_command() with a directory: checking error message
 */
Test(check_command, test4)
{
    stream = strdup("./src");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#4: malloc error: %s\n", strerror(errno));
    }
    check_command(&shell, shell.ast);
    cr_assert_stderr_eq_str("./src: Permission denied.\n");
}

/*
 * Test #5
 * -------
 * Tests check_command() with a valid command
 */
Test(check_command, test5)
{
    stream = strdup("ls");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#5: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(check_command(&shell, shell.ast), 1);
}

/*
 * Test #6
 * -------
 * Tests check_command() with a non existing command: checking return value
 */
Test(check_command, test6)
{
    stream = strdup("command_does_not_exist");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#6: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(check_command(&shell, shell.ast), 0);
}

/*
 * Test #7
 * -------
 * Tests check_command() with a non existing command: checking error message
 */
Test(check_command, test7)
{
    stream = strdup("command_does_not_exist");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#7: malloc error: %s\n", strerror(errno));
    }
    check_command(&shell, shell.ast);
    cr_assert_stderr_eq_str("command_does_not_exist: Command not found.\n");
}

/*
 * Test #8
 * -------
 * Tests check_command() with an existing command (NULL env): checking error message
 */
Test(check_command, test8)
{
    stream = strdup("ls");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#8: malloc error: %s\n", strerror(errno));
    }
    release_variables(shell.heads->environment);
    shell.heads->environment = NULL;
    cr_assert_eq(check_command(&shell, shell.ast), 0);
}
