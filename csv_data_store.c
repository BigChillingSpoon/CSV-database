//
// Created by vikslajvant on 02/11/2025.
//

#include "csv_data_store.h"

TABLE load_table_from_csv_file(const CSV_FILE *csv_file_info) {
    TABLE table;
    init_table(&table);
    table.file_info.input_path = csv_file_info->input_path;
    table.file_info.output_path = csv_file_info->output_path;

    FILE *file = fopen(csv_file_info->input_path, "rb");

    if (file == NULL) {
        critical_error("Input file cannot be opened\n");
    }

    char line[MAX_LINE_LENGTH];
    int line_index = 0;
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        remove_newline(line);
        if (line_index == 0)
            convert_to_columns(&table, line);
        else
            add_row(line, &table);
        line_index++;
    }
    if (line_index == 0) {
        warning("File '%s' is empty",csv_file_info->input_path);
    }

    printf("Table was succesfully loaded with %d columns and %d rows...\n", table.number_of_columns, table.number_of_rows);
    fclose(file);
    return table;
}
void save_table_to_csv_file(TABLE* table) {
    FILE *file = fopen(table->file_info.output_path, "w");
    if (file == NULL) {
        critical_error("Unable to save the database: File '%s' cannot be opened\n", table->file_info.output_path);
    }

    //saves columns
    insert_columns_to_file(table, file);
    //saves rows
    insert_rows_to_file(table, file);
    fclose(file);
}

void insert_columns_to_file(TABLE* table, FILE* file) {
    char* column_line = (char*) malloc(MAX_LINE_LENGTH * sizeof(char));
    column_line[0] = '\0';

    for (int i = 0; i < table->number_of_columns; i++) {
        strcat(column_line, table->columns[i].name);
        if (i < table->number_of_columns - 1)
            strcat(column_line, ",");
    }
    strcat(column_line, "\n");
    fwrite(column_line, strlen(column_line), 1, file);

    free(column_line);
}

void insert_rows_to_file(TABLE* table, FILE* file) {
    char* row_line = (char*) malloc(MAX_LINE_LENGTH * sizeof(char));

    for (int i = 0; i < table->number_of_rows; i++) {
        row_line[0] = '\0';

        for (int j = 0; j < table->rows[i].number_of_values; j++) {
            strcat(row_line, table->rows[i].values[j]);
            if (j < table->rows[i].number_of_values - 1)
                strcat(row_line, ",");
        }
        strcat(row_line, "\n");
        fwrite(row_line, strlen(row_line), 1, file);
    }

    free(row_line);
}