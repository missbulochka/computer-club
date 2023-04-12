#include <iostream>
#include <algorithm>
#include "funcs_for_id.h"

bool find_some(std::vector<std::string>& collection, std::string& some) {
    auto res = std::find(std::cbegin(collection), std::cend(collection), some);
    return res != std::cend(collection);
}

void id11(hh_mm& time, const std::string& name) {
    print_time(time, false);
    std::cout << 11 << ' ' << name << '\n';
}

void id13(hh_mm& time, const std::string& error_msg) {
    print_time(time, false);
    std::cout << 13 << ' ' << error_msg << '\n';
}

void id1(club_info& work_info, hh_mm& time, std::string& name) {
    std::cout << work_info.current_str << '\n';

    if (find_some(work_info.queue_clients, name) || find_some(work_info.who_sits, name)) {
        id13(time, "YouShallNotPass");
        return;
    }
    if (!time_is_less_or_equal_then(work_info.start_time, time)
        || !time_is_less_or_equal_then(time, work_info.end_time)) {
        id13(time, "NotOpenYet");
        return;
    }
}

void id2() {}

void id3(club_info& work_info, hh_mm& time, std::string& name) {
    const auto empty_table = [](const auto queue) {
        return std::find(std::cbegin(queue), std::cend(queue), "") != std::cend(queue);
    };

    std::cout << work_info.current_str << '\n';

    if (empty_table(work_info.queue_clients)) {
        id13(time, "ICanWaitNoLonger");
    }
    if (work_info.queue_clients.size() > work_info.number_of_tables) {
        id11(time, name);
    }
}

void id4() {}
