/*
** EPITECH PROJECT, 2024
** tests/criterion/variables/_unset_variable.c
** File description:
** Tests unset_variable() function
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
 * Tests unset_variable() with a NULL linked list's head
 */
Test(unset_variable, test1, .fini = teardown)
{
    cr_assert_eq(unset_variable(&head, NULL), 0, "KO: Null env");
}

/*
 * Test #2
 * -------
 * Tests unset_variable() with a NULL variable name
 */
Test(unset_variable, test2, .fini = teardown)
{
    head = create_environment(environ);

    if (!head) {
        cr_assert_eq(1, 0, "KO: T#2: Get environment: %s\n", strerror(errno));
    }
    cr_assert_eq(unset_variable(&head, NULL), 0);
}

/*
 * Test #3
 * -------
 * Tests that unset_variable() on the first node doesn't erase head's pointer
 */
Test(unset_variable, test3, .fini = teardown)
{
    head = create_environment(environ);

    if (!head) {
        cr_assert_eq(1, 0, "KO: T#3: Get environment: %s\n", strerror(errno));
    }
    unset_variable(&head, head->name);
    cr_assert_neq(head, NULL);
}

/*
 * Test #4
 * -------
 * Tests unset_variable() with a non existing variable name
 */
Test(unset_variable, test4, .fini = teardown)
{
    head = create_environment(environ);

    if (!head) {
        cr_assert_eq(1, 0, "KO: T#4: Get environment: %s\n", strerror(errno));
    }
    cr_assert_eq(unset_variable(&head, "ajzhuahgzhghegzhlazajhbjhffghezf"), 0);
}

/*
 * Test #5
 * -------
 * Tests unset_variable() with a existing variable name
 */
Test(unset_variable, test5, .fini = teardown)
{
    head = create_environment(environ);

    if (!head) {
        cr_assert_eq(1, 0, "KO: T#5: Get environment: %s\n", strerror(errno));
    }
    cr_assert_eq(unset_variable(&head, "PWD"), 0, "KO: Existing variable");
}

/*
 * Test #6
 * -------
 * Tests unset_variable() with only one variable in the linked list
 */
Test(unset_variable, test6, .fini = teardown)
{
    head = malloc(sizeof(variable_t));

    if (!head) {
        cr_assert_eq(1, 0, "KO: T#2: malloc error: %s\n", strerror(errno));
    }
    head->name = strdup("NEWLY_CREATED_VARIABLE");
    head->value = strdup("value");
    head->next = NULL;
    cr_assert_eq(unset_variable(&head, "NEWLY_CREATED_VARIABLE"), 0);
}
