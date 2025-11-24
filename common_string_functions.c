//
// Created by vikslajvant on 13/11/2025.
//

#include "common_string_functions.h"

int get_count_of_elements(const char *source_str, char delimeter) {
    int count = 0;
    int i = 0;
    while (source_str[i] != '\0') {
        if (source_str[i] == delimeter) {
            count++;
        }
        i++;
    }
    return *source_str == '\0' ? 0 : ++count;//only if string is empty then count is O otherwise count is 1 or more
}

void remove_newline(char* string) {
    int index = 0;

    while (string[index] != '\0') {
        if (string[index] == '\n') {
            string[index] = '\0';
            break;
        }
        index++;
    }
}
