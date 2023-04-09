cmake_minimum_required(VERSION 3.24)
project(computer_club)

set(CMAKE_CXX_STANDARD 17)

set(source_list
        src/main.cpp)

add_executable(${PROJECT_NAME} ${source_list})
