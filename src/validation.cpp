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

void validation::time_validation() {
    std::string block_1 = current_str.substr(0, current_str.find(' '));
    std::string block_2 = current_str.substr(current_str.find(' ') + 1);

    auto check_time = [this](std::string& block) {
        size_t pos = block.find(':');
        if (!this->uint_validation(block.substr(0, pos)) || std::stol(block.substr(0, pos)) >= 24)
            error_msg();
        if (!this->uint_validation(block.substr(pos + 1)) || std::stol(block.substr(pos + 1)) >= 60) {
            error_msg();
        }
        return std::make_pair(block.substr(0, pos), block.substr(pos + 1));
    };

    start_time = check_time(block_1);
    end_time = check_time(block_2);
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
            case (2): time_validation(); break;
            case (3):
                if (uint_validation(current_str)) {
                    price = std::stol(current_str, nullptr, 0);
                }
                break;
            default:
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
