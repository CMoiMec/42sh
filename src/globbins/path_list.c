/*
** EPITECH PROJECT, 2024
** src/globbins/path_list.c
** File description:
** Function for path chained list
** Author: @cmoimec
*/

#include "globbins.h"

/*
 * Function: free_path
 * -------------------
 * Free the paht_t chained list
 *
 * - list: the chained list
 */
void free_path(path_t **list)
{
    path_t *tmp;

    for (path_t *node = *list; node; node = tmp) {
        tmp = node->next;
        free(node->path);
        free(node);
    }
    *list = NULL;
    return;
}

/*
 * Function: delete_node
 * ---------------------
 * Delete the path_t node if it is in list
 *
 * - list: the path_t list
 * - node: the node that you want delete
 */
void delete_node(path_t **list, path_t *node)
{
    path_t *prev = *list;

    if (list == NULL || *list == NULL || node == NULL) {
        return;
    }
    if (*list == node) {
        *list = node->next;
        free(node->path);
        free(node);
        return;
    }
    for (; prev->next != node && prev != NULL; prev = prev->next);
    if (prev == NULL) {
        return;
    }
    prev->next = node->next;
    free(node->path);
    free(node);
    return;
}

/*
 * Function: node_file
 * -------------------
 * Return the node for a path
 *
 * - path: containing the path
 */
path_t *node_file(const char *path)
{
    path_t *node = malloc(sizeof(path_t));

    if (node == NULL) {
        return NULL;
    }
    node->path = my_strdup(path);
    if (node->path == NULL) {
        free(node);
        return NULL;
    }
    node->delete = 0;
    node->next = NULL;
    return node;
}
