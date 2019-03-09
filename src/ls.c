
#include "ls.h"

typedef struct options_t {
    int ShowAll;
} Options;

Options options;

#if defined (TRUE) || defined (FALSE)
#else
#define TRUE  1
#define FALSE 0
#endif

int LongOption(const char *arg, const char *option) {
    return StrAreEqual(arg, option);
}

int ShortOption(const char *arg, const char *option) {
    return StrAreEqual(arg, option);
}

int Option(const char *arg, const char *longOption, const char *shortOption) {
    if (longOption && LongOption(arg, longOption)) {
        return TRUE;
    }

    if (shortOption && ShortOption(arg, shortOption)) {
        return TRUE;
    }

    return FALSE;
}

void ShowHelpMenu() {
    // TODO: Implement ShowHelpMenu();
    fprintf(stdout, "<Help Menu>\n");
}

void ShowProgramVersion() {
    // TODO: Implement ShowProgramVersion();
    fprintf(stdout, "<Program Version>\n");
}

/** Arguments:
 *  --help     -h  Show help message and exit.
 *  --version      Show program version and exit.
 *  --all      -a  Show all files and directories.
 *
 */

void CheckArgs(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Usage: ls [OPTIONS] <DIR>\n");

        exit(EXIT_FAILURE);
    }

    /** Get options passed in.
     *
     */
    for (int i = 1; i < argc; i++) {
        if (StrAreEqual(argv[i], "--version")) {
            ShowProgramVersion();
            exit(EXIT_SUCCESS);
        }

        if (Option(argv[i], "--help", "-h")) {
            ShowHelpMenu();
            exit(EXIT_SUCCESS);
        }

        if (Option(argv[i], "--all", "-a")) {
            options.ShowAll = TRUE;
        }
    }
}


int main(int argc, char *argv[])
{
    options.ShowAll = FALSE;

    CheckArgs(argc, argv);

    DIR *directoryHandle = NULL;

    if ((directoryHandle = opendir(argv[argc - 1])) == NULL) {
        fprintf(stderr, "Failed to open %s\n", argv[argc - 1]);
        
        return EXIT_FAILURE;
    }

    struct dirent *directory = NULL;

    while ((directory = readdir(directoryHandle)) != NULL) {
        /** By default ignore the special files '.' and '..'.
         *
         */
        if (StrAreEqual(directory->d_name, ".") || StrAreEqual(directory->d_name, "..")) {
            continue;
        }

        /** Just like the original version, by default ignore hidden files,
         *  i.e. those whose name begins with a period.
         *
         */
        if (!options.ShowAll && directory->d_name[0] == '.') {
            continue;
        }

        printf("%s\n", directory->d_name);
    }

    closedir(directoryHandle);

    return EXIT_SUCCESS;
}
