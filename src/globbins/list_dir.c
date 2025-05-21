/*
** EPITECH PROJECT, 2024
** src/globbins/list_dir.c
** File description:
** Lists everything in a directory
** Author: @cmoimec
*/

#include "globbins.h"

/*
 * Function: my_file_type
 * ----------------------
 * Return the type of the file
 *
 * - buff: buffer fill by the lstat function
 */
int my_file_type(struct stat *buff)
{
    unsigned int tab[7] =
    {S_IFSOCK, S_IFLNK, S_IFREG, S_IFBLK, S_IFDIR, S_IFCHR, S_IFIFO};
    char tab2[7] = {'s', 'l', 'f', 'b', 'd', 'c', 'f'};

    for (int i = 0; i != 7; i ++) {
        if ((buff->st_mode & S_IFMT) == tab[i])
            return tab2[i];
    }
    return -1;
}

/*
 * Function: safely_write_to_node
 * ------------------------------
 * Writes data to a node's fields
 */
static void safely_write_to_node(path_t **list, path_t **node,
    const char *path, char *file_name)
{
    if (!*node) {
        return;
    }
    (*node)->path = concat_path_name(path, file_name);
    (*node)->next = *list;
    *list = (*node);
}

/*
 * Function: is_directory
 * ----------------------
 * return Yes if my path is a directory else False
 *
 * - path: the file path
*/
int is_directory(const char *path)
{
    struct stat buff;

    if (!path) {
        return (1);
    }
    if (stat(path, &buff) == -1)
        return 0;
    return (my_file_type(&buff) == 'd');
}

/*
 * Function: list_dir
 * ------------------
 * Make a chained list of every file in the directory
 * If the path isn't a directory a chained list containing
 * the path is returned
 *
 * - path: the path of the directory
*/
path_t *list_dir(const char *path)
{
    DIR *directory = opendir((path) ? path : ".");
    path_t *list = NULL;
    path_t *node = NULL;

    if (directory == NULL) {
        return NULL;
    }
    for (struct dirent *elem = readdir(directory); elem != NULL;
    elem = readdir(directory)) {
        if (my_strcmp("..", elem->d_name) && my_strcmp(".", elem->d_name)) {
            node = malloc(sizeof(path_t));
            safely_write_to_node(&list, &node, path, elem->d_name);
        }
    }
    closedir(directory);
    return list;
}
