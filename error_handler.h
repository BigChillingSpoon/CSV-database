//
// Created by vikslajvant on 13/11/2025.
//

#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
void critical_error(char* message,...);
void warning(char* message,...);
void error(char* message,...);
#endif //ERROR_HANDLER_H
