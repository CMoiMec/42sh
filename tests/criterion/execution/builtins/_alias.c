/*
** EPITECH PROJECT, 2024
** tests/criterion/execution/builtins/_alias.c
** File description:
** Tests b_alias() function
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
TestSuite(b_alias, .init = init, .fini = teardown);

/*
 * Test #1
 * -------
 * Tests b_alias() test default aliases (ls & grep auto colors): checking
 *  return value
 */
Test(b_alias, test1)
{
    argv = my_str_to_word_array("alias", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#1: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_alias(&shell, (const char **) argv), 0);
}

/*
 * Test #2
 * -------
 * Tests b_alias() test incomplete alias
 */
Test(b_alias, test2)
{
    argv = my_str_to_word_array("alias test", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#2: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_alias(&shell, (const char **) argv), 0);
}

/*
 * Test #3
 * -------
 * Tests b_alias() test complete alias
 */
Test(b_alias, test3)
{
    argv = my_str_to_word_array("alias test value", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#3: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_alias(&shell, (const char **) argv), 0);
}

/*
 * Test #4
 * -------
 * Tests b_alias() test complete alias (multiple arguments)
 */
Test(b_alias, test4)
{
    argv = my_str_to_word_array("alias test value1 value2 value3", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#4: malloc error: %s\n", strerror(errno));
    }
    cr_assert_eq(b_alias(&shell, (const char **) argv), 0);
}

/*
 * Test #5
 * -------
 * Tests b_alias() test no aliases: checking stdout
 */
Test(b_alias, test5)
{
    argv = my_str_to_word_array("alias", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#5: malloc error: %s\n", strerror(errno));
    }
    release_variables(shell.heads->aliases);
    shell.heads->aliases = NULL;
    b_alias(&shell, (const char **) argv);
    cr_assert_stdout_eq_str("");
}

/*
 * Test #6
 * -------
 * Tests b_alias() test default aliases: checking stdout
 */
Test(b_alias, test6, .disabled = true)
{
    argv = my_str_to_word_array("alias", " \n");
    if (!argv) {
        cr_assert_eq(1, 0, "KO: T#6: malloc error: %s\n", strerror(errno));
    }
    b_alias(&shell, (const char **) argv);
    cr_assert_stdout_neq_str("ls\t(ls --color=auto)\ngrep\t(grep --color=auto)\n");
}
