cmake_minimum_required(VERSION 3.24)
project(computer_club)

set(CMAKE_CXX_STANDARD 20)

set(source_list
        src/main.cpp
        src/validation.cpp src/validation.h)

add_executable(${PROJECT_NAME} ${source_list})
