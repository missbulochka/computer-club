#include <iostream>
#include <algorithm>
#include "funcs_for_id.h"

bool find_name(const std::vector<std::string>& queue, std::string& name) {
    return std::find(std::cbegin(queue), std::cend(queue), name) != std::cend(queue);
}

void count_to_arrive(club_info& work_info, hh_mm& time, size_t index) {
    auto hours = std::stoi(time.hours) - std::stoi(work_info.occupancy_table[index].hours);
    auto minutes = std::stoi(time.minutes) - std::stoi(work_info.occupancy_table[index].minutes);
    if (minutes < 0) {
        hours--;
        minutes += 60;
    }
    work_info.duration[index].first += hours;
    work_info.duration[index].second += minutes;
    work_info.table_revenue[index] += hours * work_info.price;
    if (minutes > 0) {
        work_info.table_revenue[index] += work_info.price;
    }
    work_info.occupancy_table[index] = {{}, {}};
}

void id11(club_info& work_info, hh_mm& time, std::string& name) {
    print_time(time, false);
    std::cout << 11 << ' ' << name << '\n';

    if (find_name(work_info.who_sits, name)) {
        size_t index = std::distance(std::cbegin(work_info.who_sits),
                                     std::find(std::cbegin(work_info.who_sits), std::cend(work_info.who_sits), name));
        count_to_arrive(work_info, time, index);
    }
    work_info.all_clients.erase(std::find(std::cbegin(work_info.all_clients), std::cend(work_info.all_clients), name));
}

void id12(club_info& work_info, hh_mm& time, size_t index) {
    if (work_info.queue_clients.empty()) {
        return;
    }

    print_time(time, false);
    std::cout << 12 << ' ' << work_info.queue_clients[0] << ' ' << index + 1 << '\n';
    work_info.who_sits[index] = work_info.queue_clients[0];
    work_info.queue_clients.erase(work_info.queue_clients.cbegin());
    work_info.occupancy_table[index] = time;
}

void id13(hh_mm& time, const std::string& error_msg) {
    print_time(time, false);
    std::cout << 13 << ' ' << error_msg << '\n';
}

void id1(club_info& work_info, hh_mm& time, std::string& name) {
    if (!time_is_less_or_equal_then(work_info.start_time, time)
        || !time_is_less_or_equal_then(time, work_info.end_time)) {
        id13(time, "NotOpenYet");
        return;
    }
    if (find_name(work_info.all_clients, name)) {
        id13(time, "YouShallNotPass");
        return;
    }
    work_info.all_clients.push_back(name);
}

void id2(club_info& work_info, hh_mm& time, std::string& name, uint16_t table_num) {
    {
        auto flag = false;
        if (!work_info.who_sits[table_num - 1].empty()) {
            id13(time, "PlaceIsBusy");
            flag = true;
        }

        if (!find_name(work_info.all_clients, name)) {
            id13(time, "ClientUnknown");
            flag = true;
        }
        if (flag) {
            return;
        }
    }

    if (find_name(work_info.who_sits, name)) {
        size_t index = std::distance(std::cbegin(work_info.who_sits),
                                     std::find(work_info.who_sits.cbegin(), work_info.who_sits.cend(), name));
        work_info.who_sits[index] = "";
        count_to_arrive(work_info, time, index);
    }
    if (find_name(work_info.queue_clients, name)) {
        work_info.queue_clients.erase(
          std::find(work_info.queue_clients.cbegin(), work_info.queue_clients.cend(), name));
    }
    work_info.who_sits[table_num - 1] = name;
    work_info.occupancy_table[table_num - 1] = time;
}

void id3(club_info& work_info, hh_mm& time, std::string& name) {
    const auto empty_table = [](const auto who_sits) {
        auto res = std::find_if(std::cbegin(who_sits), std::cend(who_sits), [](const std::string& name) {
            return name.empty();
        });
        return res != std::cend(who_sits);
    };

    if (empty_table(work_info.who_sits)) {
        id13(time, "ICanWaitNoLonger!");
        return;
    }
    if (work_info.queue_clients.size() == work_info.number_of_tables) {
        id11(work_info, time, name);
        return;
    }
    if (!find_name(work_info.queue_clients, name)) {
        work_info.queue_clients.push_back(name);
    }
}

void id4(club_info& work_info, hh_mm& time, std::string& name) {
    if (!find_name(work_info.all_clients, name)) {
        id13(time, "ClientUnknown");
        return;
    }

    if (find_name(work_info.who_sits, name)) {
        size_t index = std::distance(std::cbegin(work_info.who_sits),
                                     std::find(std::cbegin(work_info.who_sits), std::cend(work_info.who_sits), name));
        work_info.who_sits[index] = "";
        count_to_arrive(work_info, time, index);
        id12(work_info, time, index);
    }
    else if (find_name(work_info.queue_clients, name)) {
        work_info.queue_clients.erase(
          std::find(std::cbegin(work_info.queue_clients), std::cend(work_info.queue_clients), name));
    }
    work_info.all_clients.erase(std::find(std::cbegin(work_info.all_clients), std::cend(work_info.all_clients), name));
}

void expel_clients_from_club(club_info& work_info) {
    if (!work_info.all_clients.empty()) {
        std::sort(work_info.all_clients.begin(), work_info.all_clients.end());
        while (!work_info.all_clients.empty()) {
            id11(work_info, work_info.end_time, work_info.all_clients[0]);
        }
    }
}
