/*
** EPITECH PROJECT, 2024
** tests/criterion/execution/builtins/_cd.c
** File description:
** Tests b_cd() function
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
TestSuite(b_cd, .init = init, .fini = teardown);

/*
 * Test #1
 * -------
 * Tests b_cd() (HOME) with a no path given
 */
Test(b_cd, test1)
{
    argv = my_str_to_word_array("cd", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#1: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_cd(&shell, (const char **) argv), 0);
}

/*
 * Test #2
 * -------
 * Tests b_cd() (HOME) with no path given and no HOME in environment:
 *  checking error message
 */
Test(b_cd, test2)
{
    release_variables(shell.heads->environment);
    shell.heads->environment = NULL;
    argv = my_str_to_word_array("cd", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#2: malloc error: %s\n", strerror(errno));
    }
    b_cd(&shell, (const char **) argv);
    cr_assert_stderr_eq_str("cd: No home directory.\n");
}

/*
 * Test #3
 * -------
 * Tests b_cd() (HOME) with no path given and no HOME in environment:
 *  checking return value
 */
Test(b_cd, test3)
{
    release_variables(shell.heads->environment);
    shell.heads->environment = NULL;
    argv = my_str_to_word_array("cd", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#3: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_cd(&shell, (const char **) argv), 1);
}

/*
 * Test #4
 * -------
 * Tests b_cd() (HOME) with no path given and non existing HOME in
 *  environment
 */
Test(b_cd, test4)
{
    set_variable(&shell.heads->environment, "HOME", "/fake/folder/");
    argv = my_str_to_word_array("cd", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#4: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_cd(&shell, (const char **) argv), 1);
}

/*
 * Test #5
 * -------
 * Tests b_cd() (HOME) with '~'
 */
Test(b_cd, test5)
{
    argv = my_str_to_word_array("cd ~", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#5: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_cd(&shell, (const char **) argv), 0);
}

/*
 * Test #6
 * -------
 * Tests b_cd() (OLDPWD) with '-' and no OLDPWD in environment:
 *  checking error message
 */
Test(b_cd, test6)
{
    set_variable(&shell.heads->environment, "OLDPWD", NULL);
    argv = my_str_to_word_array("cd -", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#6: malloc error: %s\n", strerror(errno));
    }
    b_cd(&shell, (const char **) argv);
    cr_assert_stderr_eq_str(": No such file or directory.\n");
}

/*
 * Test #7
 * -------
 * Tests b_cd() (OLDPWD) with '-' and empty OLDPWD in environment:
 *  checking error message: branching test
 */
Test(b_cd, test7)
{
    release_variables(shell.heads->environment);
    shell.heads->environment = NULL;
    argv = my_str_to_word_array("cd -", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#7: malloc error: %s\n", strerror(errno));
    }
    b_cd(&shell, (const char **) argv);
    cr_assert_stderr_eq_str(": No such file or directory.\n");
}

/*
 * Test #8
 * -------
 * Tests b_cd() (OLDPWD) with '-' and no OLDPWD in environment:
 *  checking return value
 */
Test(b_cd, test8)
{
    release_variables(shell.heads->environment);
    shell.heads->environment = NULL;
    argv = my_str_to_word_array("cd -", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#8: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_cd(&shell, (const char **) argv), 1);
}

/*
 * Test #9
 * -------
 * Tests b_cd() (OLDPWD) with invalid '-': checking error message
 */
Test(b_cd, test9)
{
    argv = my_str_to_word_array("cd -invalid", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#9: malloc error: %s\n", strerror(errno));
    }
    b_cd(&shell, (const char **) argv);
    cr_assert_stderr_eq_str("Usage: cd [-plvn][-|<dir>].\n");
}

/*
 * Test #10
 * --------
 * Tests b_cd() (OLDPWD) with invalid '-': checking return value
 */
Test(b_cd, test10)
{
    argv = my_str_to_word_array("cd -invalid", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#10: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_cd(&shell, (const char **) argv), 1);
}

/*
 * Test #11: Warning: this tests does not correspond to TCSH
 * ---------------------------------------------------------
 * Tests b_cd() (OLDPWD) with '-' and non existing OLDPWD in
 *  environment
 */
Test(b_cd, test11)
{
    set_variable(&shell.heads->environment, "OLDPWD", "/fake/folder/");
    argv = my_str_to_word_array("cd -", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#11: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_cd(&shell, (const char **) argv), 1);
}

/*
 * Test #12
 * --------
 * Tests b_cd() (OLDPWD) with '-', existing and correct OLDPWD in environment
 */
Test(b_cd, test12)
{
    argv = my_str_to_word_array("cd -", " \n");
    set_variable(&shell.heads->environment, "OLDPWD", "/");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#12: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_cd(&shell, (const char **) argv), 0);
}

/*
 * Test #13
 * --------
 * Tests b_cd() with too many arguments: checking error message
 */
Test(b_cd, test13)
{
    argv = my_str_to_word_array("cd arg1 arg2", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#13: malloc error: %s\n", strerror(errno));
    }
    b_cd(&shell, (const char **) argv);
    cr_assert_stderr_eq_str("cd: Too many arguments.\n");
}

/*
 * Test #14
 * --------
 * Tests b_cd() with too many arguments: checking return value
 */
Test(b_cd, test14)
{
    argv = my_str_to_word_array("cd arg1 arg2", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#14: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_cd(&shell, (const char **) argv), 1);
}

/*
 * Test #15
 * --------
 * Tests b_cd() with a binary (./unit_tests): checking return value
 */
Test(b_cd, test15)
{
    argv = my_str_to_word_array("cd unit_tests", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#15: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_cd(&shell, (const char **) argv), 1);
}

/*
 * Test #16
 * --------
 * Tests b_cd() with a binary (./unit_tests): checking error message
 */
Test(b_cd, test16)
{
    argv = my_str_to_word_array("cd unit_tests", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#16: malloc error: %s\n", strerror(errno));
    }
    b_cd(&shell, (const char **) argv);
    cr_assert_stderr_eq_str("unit_tests: Not a directory.\n");
}

/*
 * Test #17
 * --------
 * Tests b_cd() with '/root' (missing permissions): checking error message
 */
Test(b_cd, test17, .disabled = true)
{
    argv = my_str_to_word_array("cd /root", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#17: malloc error: %s\n", strerror(errno));
    }
    b_cd(&shell, (const char **) argv);
    cr_assert_stderr_eq_str("/root: Permission denied.\n");
}

/*
 * Test #18
 * --------
 * Tests b_cd() with 'non_existing' (non existing dir): checking error
 *  message
 */
Test(b_cd, test18, .disabled = true)
{
    argv = my_str_to_word_array("cd non_existing", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#18: malloc error: %s\n", strerror(errno));
    }
    b_cd(&shell, (const char **) argv);
    cr_assert_stderr_eq_str("non_existing: No such file or directory.\n");
}

/*
 * Test #19
 * --------
 * Tests b_cd() with 'tests' (existing folder): checking return value
 */
Test(b_cd, test19)
{
    argv = my_str_to_word_array("cd tests", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#19: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_cd(&shell, (const char **) argv), 0);
}
