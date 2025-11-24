//
// Created by vikslajvant on 02/11/2025.
//

#ifndef CSV_DATA_STORE
#define CSV_DATA_STORE
#include "database_wrapper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LINE_LENGTH 100
TABLE load_table_from_csv_file(const CSV_FILE *csv_file_info);
void save_table_to_csv_file(TABLE *table);
void insert_columns_to_file(TABLE* table, FILE* file);
void insert_rows_to_file(TABLE* table, FILE* file);
#endif //CSV_DATA_STORE
