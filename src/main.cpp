#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <vector>
#include <algorithm>
#include "validation.h"

struct club_info {
    explicit club_info(validation& val)
        : number_of_tables(val.get_number_of_tables())
        , start_time(val.get_start_time())
        , end_time(val.get_end_time())
        , price(val.get_price())
        , queue_clients()
        , who_sits(number_of_tables, "")
        , occupancy_table(number_of_tables, {{}, {}}) {}

    uint16_t number_of_tables;
    hh_mm start_time;
    hh_mm end_time;
    uint32_t price;

    std::vector<std::string> queue_clients{};
    std::vector<std::string> who_sits;
    std::vector<hh_mm> occupancy_table;
};

void id13(hh_mm& time, std::string error_msg) {
    print_time(time, false);
    std::cout << ' ' << 13 << ' ' << error_msg << '\n';
}

void id1(club_info& work_info, hh_mm& time, std::string& name) {
    const auto find = [name](const auto queue) {
        auto res = std::find_if(std::cbegin(queue), std::cend(queue), [name](const auto exist_name) {
            return exist_name == name;
        });
        return res;
    };

    if (find(work_info.queue_clients) != std::cend(work_info.queue_clients)
        || find(work_info.who_sits) != std::cend(work_info.who_sits)) {
        id13(time, "YouShallNotPass");
    }

    if (!time_is_less_then(work_info.start_time, time) || !time_is_less_then(time, work_info.end_time)) {
        id13(time, "NotOpenYet");
    }
}

void id2() {}

void id3() {}

void id4() {}

void id_analysis(club_info& work_info, hh_mm time, uint8_t id, std::string& name, uint16_t table_num = 0) {
    switch (id) {
        case (1): id1(work_info, time, name); break;
        case (2): id2(); break;
        case (3): id3(); break;
        case (4): id4(); break;
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
    std::string current_str{};
    print_time(work_info.start_time, true);

    for (size_t line_num = 1; getline(rep_file, current_str); ++line_num) {
        if (line_num < 4) {
            continue;
        }

        std::istringstream p(current_str);
        std::vector<std::string> event(std::istream_iterator<std::string>{p}, std::istream_iterator<std::string>());

        work_info.queue_clients.emplace_back("client1");
        work_info.who_sits.emplace_back("client2");

        id_analysis(work_info, parse_time(event[0], ':'), std::stoi(event[1]), event[2]);
    }

    print_time(work_info.end_time, true);

    return 0;
}
