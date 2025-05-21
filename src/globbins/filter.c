/*
** EPITECH PROJECT, 2024
** src/globbins/filter.c
** File description:
** Sort every path
** Author: @cmoimec
*/

#include "globbins.h"

/*
 * Function: verif_seg
 * -------------------
 * Verify a part of path
 * Return true if the part is correct
 *
 * - path: a part of path
 * - schema: a part of path
 */
static int verif_seg(char *path, char *schema)
{
    char **part_shema = my_str_to_word_array(schema, "*");
    int j = 0;
    int z = 0;

    for (int i = 0; part_shema && part_shema[i]; i ++) {
        for (j = 0; path[z] && part_shema[i][j] != path[z] &&
            part_shema[i][j] != '?'; z ++);
        for (; path[z] && (part_shema[i][j] == path[z] ||
            part_shema[i][j] == '?'); z ++) {
            j ++;
        }
        if (part_shema[i][j] != '\0') {
            my_strfreev(part_shema);
            return 0;
        }
    }
    my_strfreev(part_shema);
    return !(path[z] != '\0' && schema[my_strlen(schema) - 1] != '*' &&
        schema[my_strlen(schema) - 1] != path[my_strlen(path) - 1]);
}

/*
 * Function: path_match
 * --------------------
 * Return true if the path match with the schema
 *
 * - path: the path
 * - schema: the schema
 */
static int path_match(char *path, const char *schema)
{
    int match = 1;
    char **seg_s = my_str_to_word_array(schema, "/");
    char **seg_p = my_str_to_word_array(path, "/");

    if (my_array_len(seg_s) == my_array_len(seg_p)) {
        for (int i = 0; seg_s[i] && match; i ++) {
            match = verif_seg(seg_p[i], seg_s[i]);
        }
    } else {
        match = 0;
    }
    my_strfreev(seg_s);
    my_strfreev(seg_p);
    return match;
}

/*
 * Function: filtre_path
 * ---------------------
 * Delete the node that the path
 * don't match with the shema
 *
 * - path_list: the path list
 * - schema: the shema
 */
void filtre_path(path_t **path_list, const char *schema)
{
    path_t *tmp;

    for (path_t *node = *path_list; node; node = node->next) {
        if (!path_match(node->path, schema)) {
            node->delete = 1;
        }
    }
    for (path_t *node = *path_list; node; node = tmp) {
        tmp = node->next;
        if (node->delete) {
            delete_node(path_list, node);
        }
    }
    return;
}
