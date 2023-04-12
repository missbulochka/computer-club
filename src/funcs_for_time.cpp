#include <iostream>
#include "funcs_for_time.h"

hh_mm parse_time(const std::string& str, char sep) {
    auto sep_pos = str.find(sep);
    auto block_1 = str.substr(0, sep_pos);
    if (block_1.size() == str.size()) {
        std::cout << "separator symbol error";
        exit(1);
    }
    auto block_2 = str.substr(sep_pos + 1);

    return {block_1, block_2};
}

bool time_is_less_then(const hh_mm& time_1, const hh_mm& time_2) {
    if (std::stol(time_1.hours) > std::stol(time_2.hours)) {
        return false;
    }
    if (std::stol(time_1.hours) < std::stol(time_2.hours)) {
        return true;
    }
    return (std::stol(time_1.minutes) < std::stol(time_2.minutes));
}
