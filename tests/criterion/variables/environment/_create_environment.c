/*
** EPITECH PROJECT, 2024
** tests/criterion/environment/_create_environment.c
** File description:
** Tests create_environment() function
** Author: @lszsrd
*/

// Used for errno macro
#include <errno.h>

#include "../../criterion.h"

/*
 * Variable: environment
 * ---------------------
 * Defines global environment
 */
static char **environment = NULL;

/*
 * Function: teardown
 * ------------------
 * Releases environment's test's exit
 */
static void teardown(void)
{
    my_strfreev(environment);
}

/*
 * Test #1
 * -------
 * Tests create_environment() with a NULL environment
 */
Test(create_environment, test1)
{
    cr_assert_eq(create_environment(NULL), NULL);
}

/*
 * Test #2
 * -------
 * Tests create_environment() with an empty environment variable
 */
Test(create_environment, test2, .fini = teardown)
{
    environment = my_str_to_word_array("test=0\ntest2=\n", "\n");

    if (!environment) {
        cr_assert_eq(1, 0, "KO: T#2: malloc error: %s\n", strerror(errno));
    }
    cr_assert_neq(create_environment(environment), NULL);
}

/*
 * Test #3
 * -------
 * Tests create_environment() with an invalid environment variable's name
 */
Test(create_environment, test3, .fini = teardown)
{
    environment = my_str_to_word_array("=a", "\n");

    if (!environment) {
        cr_assert_eq(1, 0, "KO: T#2: malloc error: %s\n", strerror(errno));
    }
    cr_assert_neq(create_environment(environment), NULL);
}
