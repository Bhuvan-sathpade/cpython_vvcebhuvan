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

int is_alternating(char* s, char a, char b) {
    char last = 0;
    int count = 0;
    
    for (int i = 0; s[i]; i++) {
        if (s[i] == a || s[i] == b) {
            if (s[i] == last) return 0;
            last = s[i];
            count++;
        }
    }
    
    return count;
}

int alternate(char* s) {
    int freq[26] = {0}, max_len = 0;
    int len = strlen(s);
    
    if (len < 2) return 0; // Edge case: If input is a single character, return 0

    for (int i = 0; s[i]; i++) freq[s[i] - 'a']++;
    
    for (int i = 0; i < 26; i++) {
        for (int j = i + 1; j < 26; j++) {
            int len = is_alternating(s, 'a' + i, 'a' + j);
            if (len > max_len) max_len = len;
        }
    }
    
    return max_len;
}

int main() {
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    int l = parse_int(ltrim(rtrim(readline())));
    char* s = readline();
    int result = alternate(s);
    fprintf(fptr, "%d\n", result);
    fclose(fptr);
    return 0;
}

char* readline() {
    size_t alloc_length = 1024, data_length = 0;
    char* data = malloc(alloc_length);
    
    while (1) { // Replaced 'true' with '1'
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);
        if (!line) break;
        data_length += strlen(cursor);
        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') break;
        alloc_length <<= 1;
        data = realloc(data, alloc_length);
        if (!data) return "";
    }
    
    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
        data = realloc(data, data_length);
        if (!data) return "";
    } else {
        data = realloc(data, data_length + 1);
        if (!data) return "";
        data[data_length] = '\0';
    }
    
    return data;
}

char* ltrim(char* str) {
    if (!str) return "";
    if (!*str) return str;
    while (*str != '\0' && isspace(*str)) str++;
    return str;
}

char* rtrim(char* str) {
    if (!str) return "";
    if (!*str) return str;
    char* end = str + strlen(str) - 1;
    while (end >= str && isspace(*end)) end--;
    *(end + 1) = '\0';
    return str;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);
    if (endptr == str || *endptr != '\0') exit(EXIT_FAILURE);
    return value;
}