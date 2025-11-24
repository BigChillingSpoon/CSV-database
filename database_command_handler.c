
#include "database_command_handler.h"

int parse_command(ACTION_TYPE *out_action, char *out_input_data) {
    int input_data_length = (int)strlen(out_input_data);
    if (input_data_length == 0) {
        error("Input data is empty\n");
        return -1;
    }

    char c = '\0';
    char action_string[MAX_COMMAND_LENGTH] = {0};
    int i = 0;

    do {
        c = out_input_data[i];
        if (c == ' ' || c == '\n')
            break;
        action_string[i] = c;
        i++;
    }while (c != '\0');
    action_string[i] = '\0';

    *out_action = get_action_type(action_string);
    remove_action_from_command(out_input_data);
    remove_newline(out_input_data);

    return 0;
}

void remove_action_from_command(char* command) {
    int command_offset = 0;

    //skips action string from command
    while (command[command_offset] != '\0' && command[command_offset] != ' ')
        command_offset++;

    //skips all following blank spaces after the action
    while (command[command_offset] == ' ')
        command_offset++;

    //handles scenarios such as only action was in command, in this case return empty string
    if (command[command_offset] == '\0') {
        command[0] = '\0';
        return;
    }

    int command_index = 0;
    do {
        command[command_index++] = command[command_offset++];
    } while (command[command_index - 1] != '\0');
}

ACTION_TYPE get_action_type(char* action_string) {
    if (strcmp(action_string, "addrow") == 0) return ADD_ROW;
    if (strcmp(action_string, "addcol") == 0) return ADD_COLUMN;
    if (strcmp(action_string, "average") == 0)return GET_AVERAGE;
    if (strcmp(action_string, "max") == 0)return GET_MAXIMUM;
    if (strcmp(action_string, "min") == 0)return GET_MINIMUM;
    if (strcmp(action_string, "sum") == 0)return GET_SUM;
    if (strcmp(action_string, "exit") == 0)return EXIT;
    return UNKNOWN;
}

void operate(const CSV_FILE *csv_file_info) {
    ACTION_TYPE action;
    char input_data[MAX_COMMAND_LENGTH] = {0};
    TABLE table = load_table_from_csv_file(csv_file_info);
    do {
        fgets(input_data, MAX_COMMAND_LENGTH, stdin);
        if (parse_command(&action, input_data) == 0)
            command_execute(action, input_data, &table);
    }while (action != EXIT);

    free_table(&table);
}

void command_execute(ACTION_TYPE action, char *data, TABLE *table) {
        switch (action) {
            case ADD_ROW:
                try_add_row(data, table);
                break;
            case ADD_COLUMN:
                try_add_column(data, table);
                break;
            case GET_AVERAGE:
                try_get_average(data, table);
                break;
            case GET_MINIMUM:
                try_get_minimum(data, table);
                break;
            case GET_MAXIMUM:
                try_get_maximum(data, table);
                break;
            case GET_SUM:
                try_get_sum(data, table);
                break;
            case EXIT:
                try_save_and_exit(table);
                break;
            default:
                error("Command not found\n");
        }
}

void try_add_column(char *data, TABLE *table) {
    int num_of_row_elements = get_count_of_elements(data, ',');
    if (num_of_row_elements != table->number_of_rows) {
        error("Wrong number of rows\n");
        return;
    }

    //first token is new column -> all other tokens are row values
    char* column_name = strtok(data, " ");
    add_column(data, table);

    //now after adding the columns we can add row values
    char* token  = strtok(NULL, ",");
    int row_index = 0;
    while (token != NULL) {
        add_row_value(table->rows + row_index, token);
        token = strtok(NULL, ",");
        row_index++;
    }
    printf("Column '%s' was sucesfully added.\n", column_name);
}

void try_add_row(char* data, TABLE *table) {
    if (add_row(data, table) == 0)
        printf("Row was sucessfully added.\n");
}

void try_get_average(char *data, TABLE *table) {
    int error_code = 0;
    if (check_for_general_statistics_errors(table) != 0)
        return;
    float avg = get_column_average(table, data, &error_code);
    if (error_code == 0)
        printf("Average for column %s is %0.2f\n", data, avg);
}

void try_get_minimum(char *data, TABLE *table) {
    int error_code = 0;
    if (check_for_general_statistics_errors(table) != 0)
        return;
    int min = get_column_minimum(table, data, &error_code);
    if (error_code == 0)
        printf("Minimum for column %s is %d\n", data, min);
}

void try_get_maximum(char *data, TABLE *table) {
    int error_code = 0;
    if (check_for_general_statistics_errors(table) != 0)
        return;
    int max = get_column_maximum(table, data, &error_code);
    if (error_code == 0)
        printf("Maximum for column %s is %d\n", data, max);
}

void try_get_sum(char *data, TABLE *table) {
    int error_code = 0;
    if (check_for_general_statistics_errors(table) != 0)
        return;
    int sum = get_column_sum(table, data, &error_code);
    if (error_code == 0)
        printf("Sum for column %s is %d\n", data, sum);
}

void try_save_and_exit(TABLE *table) {
    printf("Saving table to file %s\n", table->file_info.output_path);
    //print_table(table);
    save_table_to_csv_file(table);
}

int check_for_general_statistics_errors(TABLE *table) {
    if (table == NULL) {
        critical_error("The table pointer is NULL\n");
    }
    if (table->number_of_rows == 0) {
        error("The table is empty. No row was found\n");
        return 1;
    }
    if (table->number_of_columns == 0) {
        error("The table is empty. No column was found\n");
        return -1;
    }

    return 0;
}