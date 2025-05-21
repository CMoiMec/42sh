/*
** EPITECH PROJECT, 2024
** src/globbins/globbins.h
** File description:
** Defines builtins' prototypes
** Author: @cmoimec
*/

#pragma once

// used for opendir(), readdir() and closedir() function
#include <sys/types.h>
#include <dirent.h>
// used for stat struct
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/stat.h>



// #include "shell.h"
#include "my.h"

/*
 * Structure: path_t
 * -----------------
 * Lists of paths
 */

typedef struct path_s {
    char *path;
    int delete;
    struct path_s *next;
} path_t;


/*
 * Parsing function's prototypes definition
 * ----------------------------------------
 */
int globbins_in_str(const char *schema);
int my_array_len(char **array);
char *concat_path_schema(const char *path, const char *schema);
char *concat_path_name(const char *path, char *name);


/*
 * Path chained list function's prototypes definition
 * --------------------------------------------------
 */
path_t *node_file(const char *path);
void concat_list(path_t **l1, path_t **l2);
void free_path(path_t **list);
void delete_node(path_t **list, path_t *node);


/*
 * File and directory function's prototypes definition
 * ---------------------------------------------------
 */
path_t *list_dir(const char *path);
int is_directory(const char *path);
int my_file_type(struct stat *buff);


/*
 * Completion function's prototypes definition
 * -------------------------------------------
 */
path_t *path_completion(const char *path, const char *schema);


/*
 * Filter function's prototypes definition
 * ---------------------------------------
 */
void filtre_path(path_t **path_list, const char *schema);
