/*
** EPITECH PROJECT, 2024
** src/shell/parse_flags.c
** File description:
** Parses shell's flags
** Author: @WilliamBSITT
*/

// Used for strcmp() prototype
#include <string.h>
// Used for (d)printf() prototype
#include <stdio.h>

#include "shell.h"

/*
 * Function: display_version
 * -------------------------
 * Displays 42sh's version
 *
 * Returns: 0
 */
static int display_version(void)
{
    printf("%s\n", SHELL_VERSION);
    return (0);
}

/*
 * Function: display_help
 * ----------------------
 * Displays help
 *
 * Returns: 0
 */
static int display_help(void)
{
    display_version();
    printf("\n--help\t\tprint this message and exit\n");
    printf("--version\tprint the version shell variable and exit\n");
    printf("\nSee the 42sh(1) manual page for detailed information.\n");
    return (0);
}

/*
 * Function: parse_flags
 * ---------------------
 * Parses shell's flags
 *
 * - argc: arguments count
 * - argv: arguments
 * - shell: shell's structure
 *
 * Returns: 0 if shell should not be started, 1 otherwise
 */
int parse_flags(int argc, const char **argv, shell_t *shell)
{
    if (argc < 2) {
        return (1);
    }
    if (argv[1]) {
        if (!strcmp(argv[1], "--version") || !strcmp(argv[1], "-v")) {
            return (display_version());
        }
        if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")) {
            return (display_help());
        }
        if (!strcmp(argv[1], "--ncurses") || !strcmp(argv[1], "-n")) {
            return (initialize_ncurses(shell));
        }
    }
    dprintf(2, "Unknown option: \'%s\'\nUsage: %s [ -vh ].\n",
        argv[1], argv[0]);
    return (0);
}
