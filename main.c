#include <stdio.h>
#include "database_command_handler.h"
#include "input_data_parser.h"
int main(int argc, char *argv[]){
    CSV_FILE csv_file_info;
    parse_input_data(&csv_file_info,argv,argc);
    operate(&csv_file_info);
    return 0;
}