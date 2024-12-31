#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/types.h>

void to_lower(char *str) {
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

int search_in_file(const char *file_path, const char *pattern, int ignore_case) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    char line[1024];
    size_t line_number = 1;
    char *found;

    while (fgets(line, sizeof(line), file)) {
        char line_copy[1024];
        strcpy(line_copy, line);

        // If case-insensitive, convert line and pattern to lowercase
        if (ignore_case) {
            to_lower(line_copy);
        }

        if (ignore_case) {
            char pattern_lower[strlen(pattern) + 1];
            strcpy(pattern_lower, pattern);
            to_lower(pattern_lower);
            found = strstr(line_copy, pattern_lower);
        } else {
            found = strstr(line_copy, pattern);
        }

        if (found) {
            printf("Found in %s: Line %zu: %s", file_path, line_number, line);
        }
        line_number++;
    }

    fclose(file);
    return 0;
}

void search_in_directory(const char *path, const char *pattern, int ignore_case) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror("Failed to open directory");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Skip the current and parent directory entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Build the full path of the file
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (entry->d_type == DT_DIR) {
            search_in_directory(full_path, pattern, ignore_case);
        } else if (entry->d_type == DT_REG) {
            search_in_file(full_path, pattern, ignore_case);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <pattern> <directory> [--ignore-case]\n", argv[0]);
        return 1;
    }

    const char *pattern = argv[1];
    const char *path = argv[2];
    int ignore_case = 0;

    // Check for ignore-case flag
    if (argc == 4 && strcmp(argv[3], "--ignore-case") == 0) {
        ignore_case = 1;
    }

    search_in_directory(path, pattern, ignore_case);

    return 0;
}
