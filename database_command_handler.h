//
// Created by vikslajvant on 02/11/2025.
//

#ifndef DATABASE_COMMAND_HANDLER_H
#define DATABASE_COMMAND_HANDLER_H
#include "database_wrapper.h"
#include "csv_data_store.h"
#include "error_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100
typedef enum {
    ADD_ROW,
    ADD_COLUMN,
    GET_AVERAGE,
    GET_MINIMUM,
    GET_MAXIMUM,
    GET_SUM,
    EXIT,
    UNKNOWN
}ACTION_TYPE;

void operate(const CSV_FILE *csv_file_info);
int parse_command(ACTION_TYPE *out_action, char *out_input_data);
ACTION_TYPE get_action_type(char* action_string);
void command_execute(ACTION_TYPE action,char *data, TABLE *table);
void try_add_row(char* data, TABLE *table);
void try_add_column(char* data, TABLE *table);
void try_get_average(char* data, TABLE *table);
void try_get_minimum(char* data, TABLE *table);
void try_get_maximum(char* data, TABLE *table);
void try_get_sum(char* data, TABLE *table);
void try_save_and_exit(TABLE *table);
void remove_action_from_command(char* command);
void print_table_statistics(const TABLE *table);

int check_for_general_statistics_errors(TABLE *table);
#endif //DATABASE_COMMAND_HANDLER_H
