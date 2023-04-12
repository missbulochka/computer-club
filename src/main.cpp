#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <vector>
#include "validation.h"
#include "funcs_for_id.h"

void id_analysis(club_info& work_info, hh_mm time, uint8_t id, std::string& name, uint16_t table_num = 0) {
    switch (id) {
        case (1): id1(work_info, time, name); break;
        case (2): id2(work_info, time, name, table_num); break;
        case (3): id3(work_info, time, name); break;
        case (4): id4(work_info, time, name); break;
        default: std::cout << "something go wrong"; exit(1);
    }
}

int main() {
    std::string file = "../test_files/report_file_1.txt";
    validation val(file);

    std::ifstream rep_file(file);
    if (!rep_file.is_open()) {
        std::cout << "Unable to open the report file";
        exit(1);
    }
    club_info work_info(val);
    print_time(work_info.start_time, true);

    for (size_t line_num = 1; getline(rep_file, work_info.current_str); ++line_num) {
        if (line_num < 4) {
            continue;
        }

        std::istringstream p(work_info.current_str);
        std::vector<std::string> event(std::istream_iterator<std::string>{p}, std::istream_iterator<std::string>());

        std::cout << work_info.current_str << '\n';
        id_analysis(work_info, parse_time(event[0], ':'), std::stoi(event[1]), event[2]);
    }

    print_time(work_info.end_time, true);

    return 0;
}
