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

int validate_db_header(int fd, struct db_header_t **headerOut) {
    if (fd < 0) {
        printf("Invalid file descriptor.\n");
        return STATUS_ERROR;
    }

    struct db_header_t *header = calloc(1, sizeof(struct db_header_t));

    if (header == NULL) {
        printf("Failed to allocate memory for DB header.\n");
        return STATUS_ERROR;
    }

    if (read(fd, header, sizeof(struct db_header_t)) != sizeof(struct db_header_t)) {
        perror("read");
        free(header);
        return STATUS_ERROR;
    }

    header->magic     = ntohl(header->magic);
    header->version   = ntohs(header->version);
    header->count     = ntohs(header->count);
    header->file_size = ntohl(header->file_size);

    if (header->magic != HEADER_MAGIC) {
        printf("Invalid header magic number.\n");
        free(header);
        return STATUS_ERROR;
    }

    if (header->version != CURRENT_VERSION) {
        printf("Invalid version. Expected version is %d.\n", CURRENT_VERSION);
        free(header);
        return STATUS_ERROR;
    }

    struct stat db_stat = {0};
    fstat(fd, &db_stat);

    if (header->file_size != db_stat.st_size) {
        printf("Incorrect file size.\n");
        free(header);
        return STATUS_ERROR;
    }

    *headerOut = header;
}

int output_file(int fd, struct db_header_t *header/*, struct employee_t *employees*/) {
    if (fd < 0) {
        printf("Invalid file descriptor.\n");
        return STATUS_ERROR;
    }

    header->magic     = htonl(header->magic);
    header->version   = htons(header->version);
    header->count     = htons(header->count);
    header->file_size = htonl(header->file_size);

    lseek(fd, 0, SEEK_SET);
    write(fd, header, sizeof(struct db_header_t));

    return STATUS_SUCCESS;
}

void list_employees(struct db_header_t *header, struct employee_t *employees) {
}

int add_employee(struct db_header_t *header, struct employee_t *employees, char *add_string) {
}

int read_employees(int fd, struct db_header_t *header, struct employee_t **employeesOut) {
}
