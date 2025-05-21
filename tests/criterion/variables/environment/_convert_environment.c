/*
** EPITECH PROJECT, 2024
** tests/criterion/environment/_convert_environment.c
** File description:
** Tests convert_environment() function
** Author: @lszsrd
*/

// Used for errno macro
#include <errno.h>

#include "../../criterion.h"

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
 * Tests convert_environment() with a NULL linked list's head
 */
Test(convert_environment, test1)
{
    cr_assert_eq(convert_environment(NULL), NULL);
}

/*
 * Test #2
 * -------
 * Tests convert_environment() with a valid linked list's head
 */
Test(convert_environment, test2, .fini = teardown)
{
    head = create_environment(environ);

    if (!head) {
        cr_assert_eq(1, 0, "KO: T#2: Get environment: %s\n", strerror(errno));
    }
    cr_assert_neq(convert_environment(head), NULL);
}
