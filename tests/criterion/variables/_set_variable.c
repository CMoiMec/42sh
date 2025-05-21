/*
** EPITECH PROJECT, 2024
** tests/criterion/variables/_set_variable.c
** File description:
** Tests set_variable() function
** Author: @lszsrd
*/

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
 * Tests set_variable() with a NULL linked list's head
 */
Test(set_variable, test1, .fini = teardown)
{
    cr_assert_eq(set_variable(&head, NULL, NULL), 0);
}

/*
 * Test #2
 * -------
 * Tests set_variable() with a NULL variable name
 */
Test(set_variable, test2, .fini = teardown)
{
    head = create_environment(environ);

    if (!head) {
        cr_assert_eq(1, 0, "KO: T#2: Get environment: %s\n", strerror(errno));
    }
    cr_assert_eq(set_variable(&head, NULL, NULL), 0);
}

/*
 * Test #3
 * -------
 * Tests set_variable() with a NULL variable value
 */
Test(set_variable, test3, .fini = teardown)
{
    head = create_environment(environ);

    if (!head) {
        cr_assert_eq(1, 0, "KO: T#3: Get environment: %s\n", strerror(errno));
    }
    cr_assert_eq(set_variable(&head, "test", NULL), 1);
}

/*
 * Test #4
 * -------
 * Tests set_variable() with a correct intended usage (creating a variable)
 */
Test(set_variable, test4, .fini = teardown)
{
    head = create_environment(environ);

    if (!head) {
        cr_assert_eq(1, 0, "KO: T#4: Get environment: %s\n", strerror(errno));
    }
    cr_assert_eq(set_variable(&head, "NAME", "value"), 1);
}

/*
 * Test #4
 * -------
 * Tests set_variable() with a correct intended usage (updating a variable)
 */
Test(set_variable, test5, .fini = teardown)
{
    head = create_environment(environ);

    if (!head) {
        cr_assert_eq(1, 0, "KO: T#5: Get environment: %s\n", strerror(errno));
    }
    cr_assert_eq(set_variable(&head, "PWD", "value"), 1);
}
