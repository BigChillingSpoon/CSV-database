//
// Created by vikslajvant on 02/11/2025.
//

#ifndef DATABASE_WRAPPER_H
#define DATABASE_WRAPPER_H
#define MAX_COLUMN_NAME_LENGTH 50
#define MAX_SINGLE_VALUE_LENGTH 50
#define CHUNK_SIZE 10
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "common_string_functions.h"
#include "error_handler.h"
typedef struct  {
   char *input_path;
   char *output_path;
}CSV_FILE;

typedef struct {
    int index; // represent order of a column
    char name[MAX_COLUMN_NAME_LENGTH]; //name of specific column
}COLUMN;

typedef struct {
    int index; //represents order of a row
    char** values; //values from csv splat into separate values
    int number_of_values; //number of elements in array values
    int values_capacity; // for how many values is allocated memory
}ROW;

typedef struct {
    CSV_FILE file_info;
    ROW* rows; //all rows that table contains
    COLUMN* columns; //all columns that table contains
    int number_of_rows; //number of elements in array columns
    int number_of_columns; //number of elements in array rows
    int columns_capacity; // for how many columns is allocated memory
    int rows_capacity;// for how many rows is allocated memory
}TABLE;

void convert_to_columns(TABLE* table, char* data);

int add_row(char *data, TABLE *table);
void add_column(const char *data, TABLE* table);

float get_column_average(const TABLE *table, const char* target_column_name, int *error_code);
int get_column_minimum(const TABLE *table, const char* target_column_name, int *error_code);
int get_column_maximum(const TABLE *TABLE, const char* target_column_name, int *error_code);
int get_column_sum(const TABLE *TABLE, const char* target_column_name, int *error_code);
void init_table(TABLE *table);
void free_table(TABLE *table);
void increase_column_memory(TABLE *table);
void increase_row_memory(TABLE *table);
void increase_row_value_memory(ROW* row);
void add_row_value(ROW* row, char* data);
int get_column_index_by_name(const TABLE *table, const char* target_column_name, int *error_code);
#endif //DATABASE_WRAPPER_H
