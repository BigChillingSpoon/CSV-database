//
// Created by vikslajvant on 19/11/2025.
//

#include "input_data_parser.h"
void parse_input_data(CSV_FILE *csv_file_info, char *argv[], int argc) {
    int input_path_provided = 0;
    int output_path_provided = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--output") == 0) {
            if (i + 1 < argc && is_valid_csv_file_path(argv[i + 1])) {
                csv_file_info->output_path = malloc(strlen(argv[i + 1]) + 1);
                strcpy(csv_file_info->output_path, argv[++i]);
                output_path_provided = 1;
            }
            else {
                critical_error("Output file path is not valid.\n");
            }
        }
        else if (strcmp(argv[i], "--input") == 0) {
            if (i + 1 < argc && is_valid_csv_file_path(argv[i+1])) {
                csv_file_info->input_path = malloc(strlen(argv[i + 1]) + 1);
                strcpy(csv_file_info->input_path, argv[++i]);
                input_path_provided = 1;
            }
            else {
                critical_error("Input file path is not valid.\n");
            }
        }
        else
            critical_error("Invalid command line arguments.\n");
    }

    if (!output_path_provided)
        critical_error("Output file path was not provided.\n");
    if (!input_path_provided)
        critical_error("Input file path was not provided.\n");

}

int is_valid_csv_file_path(const char *path) {
    const char *dot = strrchr(path, '.');
    return (dot && strcmp(dot, ".csv") == 0);
}


