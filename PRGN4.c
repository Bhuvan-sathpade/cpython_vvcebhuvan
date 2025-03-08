#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
int parse_int(char*);
char* caesarCipher(char*, int);

char* caesarCipher(char* s, int k) {
    int len = strlen(s);
    char* encrypted = malloc(len + 1);
    if (!encrypted) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    k = k % 26; // Normalize k to avoid unnecessary large shifts
    
    for (int i = 0; i < len; i++) {
        char ch = s[i];
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            encrypted[i] = base + (ch - base + k) % 26;
        } else {
            encrypted[i] = ch; // Keep non-alphabetic characters unchanged
        }
    }
    encrypted[len] = '\0';
    return encrypted;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    if (!fptr) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    int n = parse_int(ltrim(rtrim(readline())));
    char* s = readline();
    int k = parse_int(ltrim(rtrim(readline())));

    char* result = caesarCipher(s, k);

    fprintf(fptr, "%s\n", result);

    free(result);
    free(s);
    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    if (!data) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    while (true) {
        char* cursor = data + data_length;
        if (!fgets(cursor, alloc_length - data_length, stdin)) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length *= 2;
        data = realloc(data, alloc_length);

        if (!data) {
            perror("Memory reallocation failed");
            exit(EXIT_FAILURE);
        }
    }

    if (data_length > 0 && data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return NULL;
    }

    while (*str != '\0' && isspace((unsigned char)*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return NULL;
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace((unsigned char)*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        fprintf(stderr, "Invalid integer input\n");
        exit(EXIT_FAILURE);
    }

    return value;
}