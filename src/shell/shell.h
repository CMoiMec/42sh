/*
** EPITECH PROJECT, 2024
** src/shell.h
** File description:
** Defines shell's structure and prototypes
** Author: @lszsrd
*/

#pragma once

// Used for FILE structure
#include <stdio.h>
// Used for boolean macros
#include <stdbool.h>

#include "variables.h"
#include "parser.h"
#include "history.h"

/*
 * Macro: SHELL_VERSION
 * --------------------
 * Current shell's revision
 */
#define SHELL_VERSION "42sh 3.22.00 (Epitech) 2024-06-10"

/*
 * Structure: linked_list_head_t
 * -----------------------------
 * Defines shell's linked lists' heads nodes
 */
typedef struct linked_list_head_s {
    variable_t *environment;
    variable_t *variables;
    variable_t *aliases;
    history_t *history;
} linked_list_head_t;

/*
 * Structure: file_descriptors_t
 * -----------------------------
 * Defines shell's used file descriptors
 */
typedef struct file_descriptors_s {
    int standard[2];
    int pipe[2];
} file_descriptors_t;

/*
 * Structure: shell_t
 * ------------------
 * Defines shell's structure
 */
typedef struct shell_s {
    char **environment;
    ast_t *ast;
    linked_list_head_t *heads;
    file_descriptors_t *fds;
    char *last_argument;
    int child;
    unsigned short prompt_length;
    unsigned char status;
    bool use_ncurses;
} shell_t;

/*
 * Prototypes definition
 */

int parse_flags(int argc, const char **argv, shell_t *shell);
int initialize_shell(shell_t *shell);
int initialize_ncurses(shell_t *shell);

int update_environment(shell_t *shell);
char *transform_active_dir(char *current_dir, char *home_dir);
void display_prompt(shell_t *shell);
char *read_stream(shell_t *shell);

void release_variables(variable_t *head);
void release_history_entries(history_t **head);
int cleanup_shell(shell_t *shell);

// Used for undeclared ncurses prototype: a deep ncurses ressources deallocator
void _nc_free_and_exit(int);
