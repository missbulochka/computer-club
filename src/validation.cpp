#include "validation.h"

#include <iostream>
#include <utility>
#include <cctype>
#include <fstream>

validation::validation(std::string rec_file)
    : file(std::move(rec_file))
    , number_of_tables(0)
    , start_time()
    , end_time()
    , price(0)
    , current_str()
    , last_time() {
    start_val();
}

void validation::error_msg() {
    std::cout << "Error in line:\n" << current_str;
    exit(1);
}

bool validation::uint_validation(const std::string& str) {
    for (char j : str) {
        if (std::isdigit(j)) {
            continue;
        }
        else {
            return false;
        }
    }
    return true;
}

bool validation::time_validation(const std::pair<std::string, std::string>& block) {
    if (!this->uint_validation(block.first) || std::stol(block.first) >= 24) {
        return false;
    }
    if (!this->uint_validation(block.second) || std::stol(block.second) >= 60) {
        return false;
    }
    if (block.first.size() < 2 || block.second.size() < 2) {
        return false;
    }
    return true;
}

std::pair<std::string, std::string> validation::parse_time(const std::string& str, char sep) {
    auto sep_pos = str.find(sep);
    std::string block_1 = str.substr(0, sep_pos);
    std::string block_2 = str.substr(sep_pos + 1);

    return std::make_pair(block_1, block_2);
}

bool validation::time_is_less_then(const std::pair<std::string, std::string>& time_1,
                                   const std::pair<std::string, std::string>& time_2) {
    if (std::stol(time_1.first) > std::stol(time_2.first)) {
        return false;
    }
    else if (std::stol(time_1.first) < std::stol(time_2.first)) {
        return true;
    }
    else {
        return (std::stol(time_1.second) < std::stol(time_2.second));
    }
}

void validation::start_val() {
    std::ifstream rep_file(file);

    if (!rep_file.is_open()) {
        std::cout << "Unable to open the report file";
        exit(1);
    }

    for (size_t line_num = 1; getline(rep_file, current_str); ++line_num) {
        switch (line_num) {
            case (1):
                if (uint_validation(current_str)) {
                    number_of_tables = std::stol(current_str, nullptr, 0);
                }
                break;
            case (2): {
                auto times = parse_time(current_str, ' ');
                auto block_1 = parse_time(times.first, ':');
                auto block_2 = parse_time(times.second, ':');

                if (time_validation(block_1) && time_validation(block_2) && time_is_less_then(block_1, block_2)) {
                    start_time = block_1;
                    end_time = block_2;
                }
                else {
                    error_msg();
                }
                break;
            }
            case (3):
                if (uint_validation(current_str)) {
                    price = std::stol(current_str, nullptr, 0);
                }
                break;
            default: std::cout << "def";
        }
    }
}

uint16_t validation::get_number_of_tables() {
    return number_of_tables;
}

std::pair<std::string, std::string> validation::get_start_time() {
    return start_time;
}

std::pair<std::string, std::string> validation::get_end_time() {
    return end_time;
}

uint32_t validation::get_price() {
    return price;
}
