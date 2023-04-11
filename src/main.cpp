#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <vector>
#include "validation.h"

void id_analysis(uint8_t id) {}

int main() {
    std::string file = "../test_files/report_file_1.txt";
    validation val(file);

    uint16_t number_of_tables{val.get_number_of_tables()};
    hh_mm start_time{val.get_start_time()};
    hh_mm end_time{val.get_end_time()};
    uint32_t price{val.get_price()};

    std::string current_str{};
    std::vector<std::string> queue_clients{};
    std::vector<std::string> who_sits(number_of_tables, "");
    std::vector<hh_mm> occupancy_table(number_of_tables, {{}, {}});

    std::ifstream rep_file(file);
    if (!rep_file.is_open()) {
        std::cout << "Unable to open the report file";
        exit(1);
    }

    std::cout << start_time.hours << ':' << start_time.minutes << '\n';

    for (size_t line_num = 1; getline(rep_file, current_str); ++line_num) {
        if (line_num < 4) {
            continue;
        }

        std::istringstream p(current_str);
        std::vector<std::string> event(std::istream_iterator<std::string>{p}, std::istream_iterator<std::string>());

        id_analysis(std::stoi(event[2]));
    }

    return 0;
}
