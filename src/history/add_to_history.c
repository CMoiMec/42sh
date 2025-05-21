/*
** EPITECH PROJECT, 2024
** src/history/add_to_history.c
** File description:
** Entry point of the 42sh program
** Author: @lszsrd
*/

// Used for malloc() prototype
#include <stdlib.h>
// Used for perror() prototype
#include <stdio.h>
// Used for strdup() prototype
#include <string.h>
// Used for time_t structure, time() and localtime() prototype
#include <time.h>

#include "history.h"

/*
 * Function: get_timestamp
 * -----------------------
 * Retrieves current timestamp (hour:minutes)
 *
 * - timestamp: memory area to allocate allocated buffer of the timestamp
 */
static void get_timestamp(char **timestamp)
{
    time_t global_time;
    struct tm *local_time;

    time(&global_time);
    local_time = localtime(&global_time);
    *timestamp = calloc(6, sizeof(char));
    if (!*timestamp) {
        perror("malloc");
        return;
    }
    sprintf(*timestamp, "%d:%02d", local_time->tm_hour, local_time->tm_min);
}

/*
 * Function: add_to_history
 * ------------------------
 * Adds a new node to the history
 *
 * - head: head of the history linked list
 * - command: command to add to the node
 */
void add_to_history(history_t **head, char *command)
{
    history_t *history_entry = NULL;

    if (!command) {
        return;
    }
    history_entry = malloc(sizeof(history_t));
    if (!history_entry) {
        perror("malloc");
        free(command);
        return;
    }
    history_entry->command = strdup(command);
    get_timestamp(&history_entry->timestamp);
    history_entry->next = *head;
    history_entry->prev = NULL;
    *head = history_entry;
    if ((*head)->next) {
        (*head)->next->prev = history_entry;
    }
    free(command);
}
