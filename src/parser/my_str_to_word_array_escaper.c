/*
** EPITECH PROJECT, 2024
** src/parser/my_str_to_word_array_escaper.c
** File description:
** Converts a given string to a words array, taking care of escape characters
** Author: @lszsrd
*/

// Used for calloc() prototype
#include <stdlib.h>
// Used for strchr() prototype
#include <string.h>

/*
 * Function: get_words_count
 * -------------------------
 * Gets words count in the given string
 *
 * - str: string to parse
 * - separators: separators to ignore
 *
 * Returns: actual words count
 */
static size_t get_words_count(const char *str, const char *separators)
{
    size_t words = 1;

    for (size_t i = 0; str[i]; i++) {
        if (i > 0 && str[i - 1] == '\\') {
            continue;
        }
        if (i > 0 && str[i - 1] != '\\' && strchr(separators, str[i])
            && !strchr(separators, str[i + 1])) {
            words += 1;
        }
    }
    return (words);
}

/*
 * Function: get_word_length
 * -------------------------
 * Gets size of the given string
 *
 * - str: string to parse
 * - separators: separators to ignore
 *
 * Returns: actual words length
 */
static size_t get_word_length(const char *str, const char *separators)
{
    size_t i = 0;

    for (; str[i]; i++) {
        if (i > 0 && str[i - 1] != '\\' && strchr(separators, str[i])
            && !strchr(separators, str[i + 1])) {
            break;
        }
    }
    return (i);
}

/*
 * Function: get_word
 * ------------------
 * Gets each characters at the current string's index until a separator matches
 *
 * - str: string to parse
 * - separators: separators to ignore
 * - index: current string's index
 *
 * Returns: allocated buffer without separators
 */
static char *get_word(const char *str, const char *separators, size_t *index)
{
    char *buffer = calloc(1 + get_word_length(&str[*index], separators),
        sizeof(char));

    if (!buffer) {
        return (NULL);
    }
    for (size_t i = 0; str[*index]; *index += 1) {
        if (str[*index] == '\\') {
            continue;
        }
        if (str[*index - i] != '\\'
            && strchr(separators, str[*index])) {
            (*index) += 1;
            break;
        }
        buffer[i] = str[*index];
        i += 1;
    }
    return (buffer);
}

/*
 * Function: my_str_to_word_array_escaper
 * --------------------------------------
 * Converts a given string to a words array, taking care of escape characters
 *
 * - str: string to parse
 * - separators: separators to ignore
 *
 * Returns: string array of words separated by separators
 */
char **my_str_to_word_array_escaper(const char *str, const char *separators)
{
    size_t index = 0;
    size_t words = get_words_count(str, separators);
    char **word_array = calloc(words + 1, sizeof(char *));

    for (; str[index] && strchr(separators, str[index]); index += 1);
    if (!word_array || strlen(str) == index) {
        free(word_array);
        return (NULL);
    }
    index = 0;
    for (size_t i = 0; i < words; i++) {
        for (; str[index] && strchr(separators, str[index]); index += 1);
        word_array[i] = get_word(str, separators, &index);
    }
    word_array[words] = NULL;
    return (word_array);
}
