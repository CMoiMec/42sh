/*
** EPITECH PROJECT, 2024
** src/globbins/file_completion.c
** File description:
** Complete all possible path for a given shematic
** Author: @cmoimec
*/

#include "globbins.h"
#include <string.h>

/*
 * Function: globbins_in_str
 * -------------------------
 * Return true if the is a globbins in the string
 *
 * - schema: the string
 */
int globbins_in_str(const char *schema)
{
    char *left_hook = strchr(schema, '[');
    char *right_hook = NULL;

    if (strchr(schema, '*') || strchr(schema, '?'))
        return 1;
    if (left_hook) {
        right_hook = strchr(left_hook, ']');
        if (right_hook)
            return 1;
    }
    return 0;
}

/*
 * Function: path_completion
 * -------------------------
 * Make a chained list of path according to the shema
 *
 * - path: directory in wich we search
 * - schema: shema to which the completion must correspond
*/
path_t *path_completion(const char *path, const char *schema)
{
    path_t *pos_path = list_dir(path);
    path_t *tmp_path = NULL;
    path_t *all_path = NULL;
    char *new_schema = NULL;

    if (!globbins_in_str(schema) || !is_directory(path)) {
        free_path(&pos_path);
        return node_file(path);
    }
    for (path_t *node = pos_path; node; node = node->next) {
        new_schema = concat_path_schema(node->path, schema);
        tmp_path = path_completion(node->path, new_schema);
        filtre_path(&tmp_path, schema);
        concat_list(&all_path, &tmp_path);
        free(new_schema);
    }
    free_path(&pos_path);
    return all_path;
}
