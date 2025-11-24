//
// Created by vikslajvant on 02/11/2025.
//

#include "database_wrapper.h"

void convert_to_columns(TABLE* table, char* data) {
    char delimiter = ',';
    remove_newline(data);
    char *token = strtok(data,&delimiter);
    while (token != NULL) {
        add_column(token, table);
        token = strtok(NULL, &delimiter);
    }
}

void add_column(const char* data, TABLE* table){
    int new_column_index = table->number_of_columns;
    //check if enough space is allocated for new column to add
    if (table->number_of_columns + 1 > table->columns_capacity) {
        increase_column_memory(table);
    }

    table->columns[new_column_index].index = new_column_index;
    strcpy(table->columns[new_column_index].name, data);
    table->number_of_columns++;
}

int add_row(char *data, TABLE *table) {
    char delimiter = ',';

    int new_row_index = table->number_of_rows;
    int num_of_row_values = get_count_of_elements(data, delimiter);
    if (num_of_row_values != table->number_of_columns) {
        error("Wrong number of row values. Number of row values must match number of columns\n");
        return -1;
    }

    //first check if new row can be added to allocated memory
    if (new_row_index + 1 > table->rows_capacity) {
        increase_row_memory(table);
    }
    table->rows[new_row_index].index = new_row_index;
    table->rows[new_row_index].number_of_values = 0;

    char *token = strtok(data, ",");
    while (token != NULL) {
        add_row_value(table->rows + new_row_index, token);
        token = strtok(NULL, ",");
    }
    table->number_of_rows++;

    return 0;
}

void add_row_value(ROW* row, char* data) {
    int new_row_value_index = row->number_of_values;
    if (new_row_value_index + 1 > row->values_capacity) {
        increase_row_value_memory(row);
    }
    strcpy(row->values[new_row_value_index], data);
    row->number_of_values++;
}

void init_table(TABLE *table) {
    //init columns
    table->number_of_columns = 0;
    table->columns_capacity = CHUNK_SIZE;
    table->columns = malloc(sizeof(COLUMN) * CHUNK_SIZE);

    //init rows
    table->number_of_rows = 0;
    table->rows_capacity = CHUNK_SIZE;
    table->rows = malloc(sizeof(ROW) * CHUNK_SIZE);
    for (int i = 0; i < CHUNK_SIZE; i++) {

        //init row values
        table->rows[i].values = malloc(sizeof(char *) * CHUNK_SIZE);
        table->rows[i].number_of_values = 0;
        table->rows[i].values_capacity = CHUNK_SIZE;
        for (int j = 0; j < CHUNK_SIZE; j++) {
            table->rows[i].values[j] = (char*)malloc(sizeof(char) * MAX_SINGLE_VALUE_LENGTH);
        }
    }
}

void increase_column_memory(TABLE *table) {
    table->columns_capacity += CHUNK_SIZE;
    table->columns = realloc(table->columns, (sizeof(COLUMN) * table->columns_capacity));
    if (table->columns == NULL) {
        critical_error("Memory allocation failed\n");
    }
}

void increase_row_memory(TABLE *table) {
    int old_capacity = table->rows_capacity;
    table->rows_capacity += CHUNK_SIZE;
    table->rows = realloc(table->rows,   (sizeof(ROW) * table->rows_capacity));

    if (table->rows == NULL) {
        critical_error("Row memory allocation failed\n");
    }
    //for newly allocated rows also allocate memory for new rows' values
    for (int i = old_capacity; i < table->rows_capacity; i++) {
        table->rows[i].values = malloc(sizeof(char *) * CHUNK_SIZE);
        table->rows[i].number_of_values = 0;
        table->rows[i].values_capacity = CHUNK_SIZE;
        for (int j = 0; j < CHUNK_SIZE; j++) {
            table->rows[i].values[j] = malloc(sizeof(char) * MAX_SINGLE_VALUE_LENGTH);
            if (table->rows[i].values[j] == NULL) {
                critical_error("Row values memory allocation failed\n");
            }
        }
    }
}

void increase_row_value_memory(ROW *row) {
    int old_capacity = row->values_capacity;
    row->values_capacity += CHUNK_SIZE;
    row->values = realloc(row->values, (sizeof(char *) * row->values_capacity));
    if (row->values == NULL) {
        critical_error("Row values memory allocation failed\n");
    }
    for (int i = old_capacity; i < row->values_capacity; i++) {
        row->values[i] = (char*)malloc(sizeof(char) * MAX_SINGLE_VALUE_LENGTH);
        if (row->values[i] == NULL) {
            critical_error("Row values memory allocation failed\n");
        }
    }
}

float get_column_average(const TABLE *table, const char* target_column_name, int *error_code) {
    int sum = get_column_sum(table, target_column_name, error_code);
    if (*error_code != 0) {
        return -1;
    }
    //the extra one int to float conversion is here only for removing warning in my IDE
    return  sum != 0 ? (float)sum / (float)table->number_of_rows : 0;
}

int get_column_sum(const TABLE *table, const char* target_column_name, int *error_code) {
    int column_index = get_column_index_by_name(table, target_column_name, error_code);
    if (*error_code != 0) {
        return *error_code;
    }

    int sum = 0;
    for (int i = 0; i < table->number_of_rows; i++) {
        //atoi returns as error value only 0 - this suits perfectly for this problem
        sum+= atoi(table->rows[i].values[column_index]);
    }

    return sum;
}

int get_column_index_by_name(const TABLE *table, const char* target_column_name, int *error_code) {
    int target_column_index = -1;
    for (int i = 0; i < table->number_of_columns; i++) {
        if (strcmp(table->columns[i].name, target_column_name) == 0) {
            target_column_index = table->columns[i].index;
        }
    }

    if (target_column_index < 0) {
        error("Column '%s' not found\n", target_column_name);
        (*error_code) = -1;
    }

    return target_column_index;
}

int get_column_maximum(const TABLE *table, const char* target_column_name, int *error_code) {
    int column_index = get_column_index_by_name(table, target_column_name, error_code);
    if (*error_code != 0) {
        return *error_code;
    }
    int maximum = 0;
    int row_value = 0;
    for (int i = 0; i < table->number_of_rows; i++) {
        row_value = atoi(table->rows[i].values[column_index]);
        if (row_value > maximum) {
            maximum = row_value;
        }
    }

    return maximum;
}

int get_column_minimum(const TABLE *table, const char* target_column_name, int *error_code){
    int column_index = get_column_index_by_name(table, target_column_name, error_code);
    if (*error_code != 0) {
        return *error_code;
    }

    int minium = atoi(table->rows[0].values[column_index]);
    int row_value = 0;
    for (int i = 0; i < table->number_of_rows; i++) {
        row_value = atoi(table->rows[i].values[column_index]);
        if (row_value < minium) {
            minium = row_value;
        }
    }

    return minium;
}

void free_table(TABLE *table) {
    if (table == NULL) {
        return;
    }

    //free rows
    if (table->rows != NULL) {
        for (int i = 0; i < table->rows_capacity; i++) {
            ROW* current_row = &table->rows[i];

            //free row values
            if (current_row->values != NULL) {
                for (int j = 0; j < current_row->values_capacity; j++) {
                    //free specific value string
                    if (current_row->values[j] != NULL) {
                        free(current_row->values[j]);
                        current_row->values[j] = NULL;
                    }
                }
                free(current_row->values);
                current_row->values = NULL;
            }
        }
        free(table->rows);
        table->rows = NULL;
    }

    //free columns
    if (table->columns != NULL) {
        free(table->columns);
        table->columns = NULL;
    }

    table->number_of_rows = 0;
    table->number_of_columns = 0;
    table->rows_capacity = 0;
    table->columns_capacity = 0;
}