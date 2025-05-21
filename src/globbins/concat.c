/*
** EPITECH PROJECT, 2024
** src/globbins/concat.c
** File description:
** Funciton to manipulate the list
** Author: @cmoimec
*/

#include "globbins.h"

/*
 * Function: concat_list
 * ---------------------
 * Concatenate two chained list
 *
 * - l1: first chained list
 * - l2: second chained list
 */
void concat_list(path_t **l1, path_t **l2)
{
    path_t *node = *l1;

    if (node == NULL) {
        *l1 = *l2;
        return;
    }
    for (; node->next; node = node->next);
    node->next = *l2;
    return;
}

/*
 * Function: my_strcat_a
 * ---------------------
 * Return the Concatenate string
 *
 * - dest: the first string
 * - src: the second string
 */
char *my_strcat_a(const char *dest, char const *src)
{
    int i = my_strlen(src);
    int z = my_strlen(dest);
    int k = 0;
    char *dest2 = malloc(sizeof(char) * (i + z + 1));

    if (dest2 == NULL)
        return NULL;
    dest2 = my_strcpy(dest2, dest);
    for (; src[k] != '\0'; k ++) {
        dest2[z + k] = src[k];
    }
    dest2[z + k] = '\0';
    return (dest2);
}

/*
 * Function: concat_path_name
 * --------------------------
 * Concatenate the path and the name
 *
 * - path: the path of the directory
 * - name: the file name
 */
char *concat_path_name(const char *path, char *name)
{
    char *tmp;
    char *dest;

    if (!path) {
        return (strdup(name));
    }
    if (path[my_strlen(path) - 1] != '/') {
        tmp = my_strcat_a(path, "/");
    } else {
        tmp = my_strdup(path);
    }
    if (tmp == NULL) {
        return NULL;
    }
    dest = my_strcat_a(tmp, name);
    if (dest == NULL) {
        return NULL;
    }
    free(tmp);
    return dest;
}

/*
 * Function: single_path
 * ---------------------
 * Return true if there is one directoryor file
 *
 * - path: the path
 * - schema: the shema
 */
static int single_path(const char *path, const char *schema)
{
    int nb_slash_p = 0;
    int nb_slash_s = 0;

    for (int i = 0; path[i]; i ++) {
        nb_slash_p += (path[i] == '/' && path[i + 1] != '/');
    }
    for (int i = 0; schema[i]; i ++) {
        nb_slash_s += (schema[i] == '/' && schema[i + 1] != '/');
    }
    return (nb_slash_p == nb_slash_s);
}

/*
 * Funciton: concat_path_schema
 * ----------------------------
 * Return a new shema
 *
 * - path: the current path
 * - schema: the old schema
 */
char *concat_path_schema(const char *path, const char *schema)
{
    int pos = 0;
    int i = 0;
    int tmp = 0;

    if (single_path(path, schema)) {
        return my_strdup(path);
    }
    for (int j = 0; path[j]; j ++) {
        i += (path[j] == '/');
    }
    for (int j = 0; tmp < i + 1; j ++) {
        tmp += ('/' == schema[j]);
        pos = ('/' == schema[j]) ? j : pos;
    }
    return my_strcat_a(path, &schema[pos]);
}
