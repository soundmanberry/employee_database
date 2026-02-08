#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdlib.h>

#include "common.h"
#include "file.h"
#include "parse.h"

void print_usage(char *argv[]) {
    printf("Usage: %s -n -f <database file>\n", argv[0]);
    printf("\t -n - create new database file\n");
    printf("\t -f - (required) path to database file\n");
}

int main(int argc, char *argv[]) {
    char *file_path = NULL;
    bool new_file = false;
    int db_fd = -1;

    int c;

    while ((c = getopt(argc, argv, "nf:")) != -1) {
        switch (c) {
            case 'n':
                new_file = true;
                break;
            case 'f':
                file_path = optarg;
                break;
            case '?':
                printf("Unknown option -%c\n", c);
                break;
            default:
                return STATUS_ERROR;
        }
    }

    printf("New file: %d\n", new_file);
    printf("File path: %s\n", file_path);

    if (file_path == NULL) {
        printf("File path required.\n");
        print_usage(argv);
        return 0;
    }

    if (new_file) {
        db_fd = create_db_file(file_path);

        if (db_fd == STATUS_ERROR) {
            printf("Unable to create database file.\n");
            return STATUS_ERROR;
        }
    }
    else {
        db_fd = open_db_file(file_path);

        if (db_fd == STATUS_ERROR) {
            printf("Unable to open database file.\n");
            return STATUS_ERROR;
        }
    }

    return STATUS_SUCCESS;
}
