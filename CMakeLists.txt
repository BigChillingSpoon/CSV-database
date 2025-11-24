cmake_minimum_required(VERSION 3.28.3)
project(csv_database C)

set(CMAKE_C_STANDARD 11)

add_executable(csv_database main.c
        csv_data_store.c
        csv_data_store.h
        database_wrapper.c
        database_wrapper.h
        database_command_handler.c
        database_command_handler.h
        common_string_functions.c
        common_string_functions.h
        error_handler.c
        error_handler.h
        input_data_parser.c
        input_data_parser.h
)
