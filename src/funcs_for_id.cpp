#include <iostream>
#include <algorithm>
#include "funcs_for_id.h"

void id11(hh_mm& time, const std::string& name) {
    print_time(time, false);
    std::cout << 11 << ' ' << name << '\n';
}

void id12(club_info& work_info, std::string& name, size_t index) {
    if (work_info.queue_clients.empty()) {
        return;
    }

    work_info.queue_clients.erase(work_info.queue_clients.cbegin());
    work_info.who_sits[index] = name;
}

void id13(hh_mm& time, const std::string& error_msg) {
    print_time(time, false);
    std::cout << 13 << ' ' << error_msg << '\n';
}

void id1(club_info& work_info, hh_mm& time, std::string& name) {
    const auto find_name = [name](const auto queue) {
        auto res = std::find(std::cbegin(queue), std::cend(queue), name);
        return res != std::cend(queue);
    };

    if (find_name(work_info.queue_clients) || find_name(work_info.who_sits)) {
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

    if (empty_table(work_info.queue_clients)) {
        id13(time, "ICanWaitNoLonger");
    }
    if (work_info.queue_clients.size() > work_info.number_of_tables) {
        id11(time, name);
    }
}

void id4(club_info& work_info, hh_mm& time, std::string& name) {
    const auto find_name = [name](const auto queue) {
        auto res = std::find(std::cbegin(queue), std::cend(queue), name);
        return res != std::cend(queue);
    };

    if (!find_name(work_info.queue_clients) || !find_name(work_info.who_sits)) {
        id13(time, "ClientUnknown");
        return;
    }

    auto table = std::find(std::cbegin(work_info.who_sits), std::cend(work_info.who_sits), name);
    size_t index = std::distance(std::cbegin(work_info.who_sits), table);
    work_info.who_sits[index] = "";
    id12(work_info, name, index);
}
