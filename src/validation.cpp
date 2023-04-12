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

void validation::start_val() {
    std::ifstream rep_file(file);
    if (!rep_file.is_open()) {
        std::cout << "Unable to open the report file";
        exit(1);
    }

    for (size_t line_num = 1; getline(rep_file, current_str); ++line_num) {
        try {
            if (current_str.empty()) {
                throw std::runtime_error("1");
            }

            switch (line_num) {
                case (1): table_or_price_val(); break;
                case (2): time_val(); break;
                case (3): table_or_price_val(); break;
                default: event_val(line_num);
            }
        }
        catch (...) {
            std::cout << "Error in line: " << line_num << '\n' << current_str;
            exit(1);
        }
    }
}

void validation::table_or_price_val() {
    if (!only_digit(current_str) || std::stol(current_str) == 0) {
        throw std::runtime_error("1");
    }
    number_of_tables = std::stol(current_str, nullptr, 0);
}

void validation::time_val() {
    auto times = parse_time(current_str, ' ');
    auto block_1 = parse_time(times.hours, ':');
    auto block_2 = parse_time(times.minutes, ':');

    if (only_time(block_1) && only_time(block_2) && time_is_less_then(block_1, block_2)) {
        start_time = block_1;
        end_time = block_2;
    }
    else {
        throw std::runtime_error("1");
    }
}

void validation::event_val(size_t& line_num) {
    std::istringstream p(current_str);
    std::vector<std::string> event(std::istream_iterator<std::string>{p}, std::istream_iterator<std::string>());

    if (event.size() < 3 || event.size() > 4) {
        throw std::runtime_error("1");
    }
    {
        auto time = parse_time(event[0], ':');
        if (!only_time(time) || !only_digit(event[1]) || !only_alnum(event[2])) {
            throw std::runtime_error("1");
        }

        if (std::stol(event[1]) > 4 || std::stol(event[1]) == 0) {
            throw std::runtime_error("1");
        }

        if (line_num > 4 && !time_is_less_then(last_time, time)) {
            throw std::runtime_error("1");
        }
        last_time = time;
    }
    if (event.size() == 4
        && (!only_digit(event[3]) || std::stol(event[3]) > number_of_tables || std::stol(event[3]) == 0)) {
        throw std::runtime_error("1");
    }
}

bool validation::only_digit(const std::string& str) {
    const auto find = std::find_if(std::cbegin(str), std::cend(str), [](const auto ch) { return !std::isdigit(ch); });
    return find == std::cend(str);
}

bool validation::only_alnum(const std::string& str) {
    const auto find = std::find_if(std::cbegin(str), std::cend(str), [](const auto ch) { return !std::isalnum(ch); });
    return find == std::cend(str);
}

bool validation::only_time(const hh_mm& block) {
    if (!only_digit(block.hours) || std::stol(block.hours) >= 24) {
        return false;
    }
    if (!only_digit(block.minutes) || std::stol(block.minutes) >= 60) {
        return false;
    }
    if (block.hours.size() != 2 || block.minutes.size() != 2) {
        return false;
    }
    return true;
}

uint16_t validation::get_number_of_tables() const {
    return number_of_tables;
}

hh_mm validation::get_start_time() const {
    return start_time;
}

hh_mm validation::get_end_time() const {
    return end_time;
}

uint32_t validation::get_price() const {
    return price;
}
