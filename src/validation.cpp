#include "validation.h"

#include <iostream>
#include <utility>
#include <cctype>
#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>
#include <algorithm>

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

void validation::error_msg(size_t error_line) {
    std::cout << "Error in line: " << error_line << '\n' << current_str;
    exit(1);
}

bool validation::only_digit(const std::string& str) {
    const auto find = std::find_if(std::cbegin(str), std::cend(str), [](const auto ch) { return !std::isdigit(ch); });
    return find == std::cend(str);
}

bool validation::only_alnum(const std::string& str) {
    const auto find = std::find_if(std::cbegin(str), std::cend(str), [](const auto ch) { return !std::isalnum(ch); });
    return find == std::cend(str);
}

bool validation::only_time(const std::pair<std::string, std::string>& block) {
    if (!this->only_digit(block.first) || std::stol(block.first) >= 24) {
        return false;
    }
    if (!this->only_digit(block.second) || std::stol(block.second) >= 60) {
        return false;
    }
    if (block.first.size() < 2 || block.second.size() < 2) {
        return false;
    }
    return true;
}

std::pair<std::string, std::string> validation::parse_time(const std::string& str, char sep) {
    auto sep_pos = str.find(sep);
    auto block_1 = str.substr(0, sep_pos);
    auto block_2 = str.substr(sep_pos + 1);

    return std::make_pair(block_1, block_2);
}

bool validation::time_is_less_then(const std::pair<std::string, std::string>& time_1,
                                   const std::pair<std::string, std::string>& time_2) {
    if (std::stol(time_1.first) > std::stol(time_2.first)) {
        return false;
    }
    if (std::stol(time_1.first) < std::stol(time_2.first)) {
        return true;
    }
    return (std::stol(time_1.second) < std::stol(time_2.second));
}

void validation::start_val() {
    std::ifstream rep_file(file);

    if (!rep_file.is_open()) {
        std::cout << "Unable to open the report file";
        exit(1);
    }

    for (size_t line_num = 1; getline(rep_file, current_str); ++line_num) {
        if (current_str.empty()) {
            error_msg(line_num);
        }

        switch (line_num) {
            case (1):
                if (!only_digit(current_str)) {
                    error_msg(line_num);
                }
                number_of_tables = std::stol(current_str, nullptr, 0);
                break;
            case (2): {
                auto times = parse_time(current_str, ' ');
                auto block_1 = parse_time(times.first, ':');
                auto block_2 = parse_time(times.second, ':');

                if (only_time(block_1) && only_time(block_2) && time_is_less_then(block_1, block_2)) {
                    start_time = block_1;
                    end_time = block_2;
                }
                else {
                    error_msg(line_num);
                }
                break;
            }
            case (3):
                if (!only_digit(current_str)) {
                    error_msg(line_num);
                }
                price = std::stol(current_str, nullptr, 0);
                break;
            default:
                std::istringstream p(current_str);
                std::vector<std::string> event(std::istream_iterator<std::string>{p},
                                               std::istream_iterator<std::string>());
                if (event.size() < 3) {
                    error_msg(line_num);
                }

                auto time = parse_time(event[0], ':');
                if (!only_time(time)) {
                    error_msg(line_num);
                }
                if (line_num == 4) {
                    last_time = time;
                }
                else {
                    if (!time_is_less_then(last_time, time)) {
                        error_msg(line_num);
                    }
                    last_time = time;
                }

                if (!only_digit(event[1]) || std::stol(event[1]) > 4) {
                    error_msg(line_num);
                }

                if (!only_alnum(event[2])) {
                    error_msg(line_num);
                }

                if (event.size() == 4) {
                    if (!only_digit(event[3]) || std::stol(event[3]) > number_of_tables) {
                        error_msg(line_num);
                    }
                }
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
