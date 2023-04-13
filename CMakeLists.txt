cmake_minimum_required(VERSION 3.24)
project(computer_club)

set(CMAKE_CXX_STANDARD 17)

set(source_list
        src/main.cpp
        src/validation.cpp src/validation.h
        src/types.h
        src/funcs_for_time.h src/funcs_for_time.cpp
        src/funcs_for_id.cpp src/funcs_for_id.h)

add_executable(${PROJECT_NAME} ${source_list})
