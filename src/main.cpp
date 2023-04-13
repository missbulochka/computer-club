#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <vector>
#include "validation.h"
#include "funcs_for_id.h"

void id_analysis(club_info& work_info, hh_mm time, uint8_t id, std::string& name, uint16_t table_num) {
    switch (id) {
        case (1): id1(work_info, time, name); break;
        case (2): id2(work_info, time, name, table_num); break;
        case (3): id3(work_info, time, name); break;
        case (4): id4(work_info, time, name); break;
        default: std::cout << "something go wrong"; exit(1);
    }
}

void print_revenue(club_info& work_info) {
    for (int i = 0; i < work_info.number_of_tables; ++i) {
        if (work_info.duration[i].second > 60) {
            auto hours = work_info.duration[i].second % 60;
            work_info.duration[i].first += hours;
            work_info.duration[i].second -= hours * 60;
        }

        hh_mm time = {{std::to_string(work_info.duration[i].first)}, {std::to_string(work_info.duration[i].second)}};
        if (time.hours.size() < 2) {
            time.hours.insert(0, "0");
        }
        if (time.minutes.size() < 2) {
            time.minutes.insert(0, "0");
        }

        std::cout << i + 1 << ' ' << work_info.table_revenue[i] << ' ';
        print_time(time, true);
    }
}

void id_analysis(uint8_t id) {}

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
        if (event.size() < 4) {
            event.emplace_back("0");
        }


        std::cout << work_info.current_str << '\n';
        id_analysis(work_info, parse_time(event[0], ':'), std::stoi(event[1]), event[2], std::stoi(event[3]));
    }

    expel_clients_from_club(work_info);
    print_time(work_info.end_time, true);
    print_revenue(work_info);

    return 0;
}
