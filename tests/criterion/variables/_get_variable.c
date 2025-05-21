/*
** EPITECH PROJECT, 2024
** tests/criterion/variables/_get_variable.c
** File description:
** Tests get_variable() function
** Author: @lszsrd
*/

// Used for errno macro
#include <errno.h>

#include "../criterion.h"

/*
 * Variable: environ
 * -----------------
 * Imports environment
 */
extern char **environ;

/*
 * Variable: head
 * --------------
 * Defines global environment's head node
 */
static variable_t *head = NULL;

/*
 * Function: teardown
 * ------------------
 * Releases environment's linked list at test's exit
 */
static void teardown(void)
{
    release_variables(head);
}

/*
 * Test #1
 * -------
 * Tests get_variable() with a NULL linked list's head
 */
Test(get_variable, test1)
{
    cr_assert_eq(get_variable(NULL, NULL), NULL);
}

/*
 * Test #2
 * -------
 * Tests get_variable() with a NULL variable name
 */
Test(get_variable, test2, .fini = teardown)
{
    head = create_environment(environ);

    if (!head) {
        cr_assert_eq(1, 0, "KO: T#2: Get environment: %s\n", strerror(errno));
    }
    cr_assert_eq(get_variable(head, NULL), NULL);
}

/*
 * Test #3
 * -------
 * Tests get_variable() with a NULL head but a variable name
 */
Test(get_variable, test3)
{
    cr_assert_eq(get_variable(NULL, "PWD"), NULL);
}

/*
 * Test #4
 * -------
 * Tests get_variable() with a correct intended usage
 */
Test(get_variable, test4, .fini = teardown)
{
    head = create_environment(environ);

    if (!head) {
        cr_assert_eq(1, 0, "KO: T#4: Get environment: %s\n", strerror(errno));
    }
    cr_assert_neq(get_variable(head, "PWD"), NULL);
}
