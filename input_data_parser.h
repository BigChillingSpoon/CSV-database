//
// Created by vikslajvant on 19/11/2025.
//

#ifndef INPUT_DATA_PARSER_H
#define INPUT_DATA_PARSER_H
#include "database_wrapper.h"
void parse_input_data(CSV_FILE *csv_file_info, char *argv[], int argc);
int is_valid_csv_file_path(const char *path);

#endif //INPUT_DATA_PARSER_H
