
#include "xxdc.h"

FILE* open_file(const char* filename, const char* mode) {
    FILE* file = fopen(filename, mode);

    if (file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    return file;
}

FILE* open_input_file(const char* filename) {
    return open_file(filename, "r");
}

void close_file(FILE* file) {
    if (fclose(file) == EOF) {
        fprintf(stderr, "Fatal error while attempting to close file\n");
        exit(EXIT_FAILURE);
    }
}
