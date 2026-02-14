#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "common.h"
#include "parse.h"

int create_db_header(int fd, struct db_header_t **headerOut) {
    struct db_header_t *header = calloc(1, sizeof(struct db_header_t));

    if (header == NULL) {
        printf("Failed to allocate memory for DB header.\n");
        return STATUS_ERROR;
    }

    header->magic     = HEADER_MAGIC;
    header->version   = 1;
    header->count     = 0;
    header->file_size = sizeof(struct db_header_t);

    *headerOut = header;

    return STATUS_SUCCESS;
}

void list_employees(struct db_header_t *db_header, struct employee_t *employees) {
}

int add_employee(struct db_header_t *db_header, struct employee_t *employees, char *add_string) {
}

int read_employees(int fd, struct db_header_t *db_header, struct employee_t **employeesOut) {
}

int output_file(int fd, struct db_header_t *db_header, struct employee_t *employees) {
}

int validate_db_header(int fd, struct db_header_t **headerOut) {
}
