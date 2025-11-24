//
// Created by vikslajvant on 13/11/2025.
//

#include "error_handler.h"
void critical_error(char* message, ...) {
    va_list args;
    va_start(args, message);
    fprintf(stderr, "CRITICAL ERROR:");
    vfprintf(stderr, message, args);
    fprintf(stderr,"\n");
    va_end(args);
    exit(EXIT_FAILURE);
}

void warning(char* message, ...) {
    va_list args;
    va_start(args, message);
    fprintf(stderr, "WARNING:");
    vfprintf(stderr, message, args);
    fprintf(stderr,"\n");
    va_end(args);
}

void error(char* message, ...) {
    va_list args;
    va_start(args, message);
    fprintf(stderr, "ERROR:");
    vfprintf(stderr, message, args);
    fprintf(stderr,"\n");
    va_end(args);
}