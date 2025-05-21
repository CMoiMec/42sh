/*
** EPITECH PROJECT, 2024
** tests/criterion/execution/commands/_execute_command.c
** File description:
** Tests execute_command() function
** Author: @lszsrd
*/

// Used for errno macro
#include <errno.h>
// Used for kill() prototype
#include <signal.h>

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
TestSuite(execute_command, .init = init, .fini = teardown);

/*
 * Test #1
 * -------
 * Tests execute_command(): non existing command
 */
Test(execute_command, test1)
{
    stream = strdup("this_is_not_a_command");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#1: malloc error: %s\n", strerror(errno));
    }
    execute_command(&shell, shell.ast, 1);
    cr_assert_eq(shell.status, 1);
}

/*
 * Test #2
 * -------
 * Tests execute_command(): existing command: checking return value
 */
Test(execute_command, test2)
{
    stream = strdup("ls");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#2: malloc error: %s\n", strerror(errno));
    }
    execute_command(&shell, shell.ast, 1);
    cr_assert_eq(shell.status, 0);
}

/*
 * Test #3
 * -------
 * Tests execute_command(): existing command (2): checking return value
 */
Test(execute_command, test3)
{
    stream = strdup("ls non_existing_file");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#3: malloc error: %s\n", strerror(errno));
    }
    execute_command(&shell, shell.ast, 1);
    cr_assert_eq(shell.status, 2);
}

/*
 * Test #4
 * -------
 * Tests execute_command(): causing a SIG-SEGV
 */
Test(execute_command, test4)
{
    stream = strdup(SEGFAULT_BINARY);
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#4: malloc error: %s\n", strerror(errno));
    }
    execute_command(&shell, shell.ast, 1);
    cr_assert_eq(shell.status, 139);
}

/*
 * Test #5
 * -------
 * Tests execute_command(): causing a SIG-SEGV: checking error message
 */
Test(execute_command, test5)
{
    stream = strdup(SEGFAULT_BINARY);
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#5: malloc error: %s\n", strerror(errno));
    }
    execute_command(&shell, shell.ast, 1);
    cr_assert_stderr_eq_str("Segmentation fault (core dumped)\n");
}

/*
 * Test #6
 * -------
 * Tests execute_command(): executing wrong architecture binary
 */
Test(execute_command, test6)
{
    stream = strdup(WRONG_EXEC_BINARY);
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#6: malloc error: %s\n", strerror(errno));
    }
    execute_command(&shell, shell.ast, 1);
    cr_assert_eq(shell.status, 1);
}

/*
 * Test #7
 * -------
 * Tests execute_command(): executing wrong architecture binary: checking error message
 */
Test(execute_command, test7)
{
    char error_message[1024] = {0};

    stream = strdup(WRONG_EXEC_BINARY);
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#7: malloc error: %s\n", strerror(errno));
    }
    my_strcat(error_message, WRONG_EXEC_BINARY);
    my_strcat(error_message, ": Exec format error. Wrong Architecture.\n");
    execute_command(&shell, shell.ast, 1);
    cr_assert_stderr_eq_str(error_message);
}

/*
 * Test #8
 * -------
 * Tests execute_command(): sending SIGINT signal (this test caused a VM crash)
 */
Test(execute_command, test8)
{
    stream = strdup("read");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#8: malloc error: %s\n", strerror(errno));
    }
    execute_command(&shell, shell.ast, 1);
    kill(shell.child, SIGINT);
    cr_assert_stdout_eq_str("");
}

/*
 * Test #9
 * -------
 * Tests execute_command(): testing cd
 */
Test(execute_command, test9)
{
    stream = strdup("cd");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#9: malloc error: %s\n", strerror(errno));
    }
    execute_command(&shell, shell.ast, 0);
    cr_assert_eq(shell.status, 0);
}

/*
 * Test #10
 * -------
 * Tests execute_command(): testing valid command without exit registeration
 */
Test(execute_command, test10)
{
    stream = strdup("ls");
    shell.ast = parse_stream(&shell, stream);
    if (!shell.ast) {
        cr_assert_eq(1, 0, "KO: T#10: malloc error: %s\n", strerror(errno));
    }
    execute_command(&shell, shell.ast, 0);
    cr_assert_eq(shell.status, 1);
}
