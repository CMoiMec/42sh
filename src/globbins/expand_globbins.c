/*
** EPITECH PROJECT, 2024
** src/globbins/expand_globbins.c
** File description:
** Expands globbins to a string
** Author: @lszsrd
*/

#include "globbins.h"
#include <stddef.h>

/*
 * Function: get_path
 * ------------------
 * Expands globbins to a string
 *
 * - path: path to search on
 * - argument: string to expand
 *
 * Returns: path, if given, NULL otherwise
 */
static char *get_path(char **path, const char *argument)
{
    size_t index = 0;

    if (!strchr(argument, '/')) {
        return (NULL);
    }
    for (int i = 0; argument[i]; i++) {
        if (argument[i] == '/') {
            index = (i + 1);
            continue;
        }
        if (strchr("[?*]", argument[i])) {
            break;
        }
    }
    *path = strdup(argument);
    (*path)[index] = '\0';
    return (*path);
}

/*
 * Function: concatenate_globbins_entries
 * --------------------------------------
 * Concatenates globbins' entries to a string
 *
 * - string: current list of entries
 * - entry: new entry to concatenate
 *
 * Returns: concatenated entries or NULL on errors
 */
static char *concatenate_globbins_entries(char **string, const char *new_entry)
{
    if (!*string) {
        *string = strdup(new_entry);
    } else {
        *string = realloc(*string, strlen(*string) + strlen(new_entry) + 2);
        if (!*string) {
            return (NULL);
        }
        strcat(*string, " ");
        strcat(*string, new_entry);
    }
    return (*string);
}

/*
 * Function: expand_globbins
 * -------------------------
 * Expands globbins to a string
 * Warning: Too little buffer starts a heap corruption
 *
 * - argument: string to expand
 */
char *expand_globbins(const char *binary, const char *argument)
{
    char *buffer = NULL;
    char *path = NULL;
    path_t *globbins = NULL;

    if (globbins_in_str(argument)) {
        globbins = path_completion(get_path(&path, argument), argument);
        free(path);
        buffer = strdup((globbins) ? binary : "");
    }
    for (path_t *releasing_node = NULL; globbins;) {
        buffer = concatenate_globbins_entries(&buffer, globbins->path);
        releasing_node = globbins;
        globbins = globbins->next;
        free(releasing_node->path);
        free(releasing_node);
    }
    return (buffer);
}
