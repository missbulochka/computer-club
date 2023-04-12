#ifndef COMPUTER_CLUB_FUNCS_FOR_ID_H
#define COMPUTER_CLUB_FUNCS_FOR_ID_H

#include <vector>
#include "validation.h"

struct club_info {
    explicit club_info(const validation& val)
        : number_of_tables(val.get_number_of_tables())
        , start_time(val.get_start_time())
        , end_time(val.get_end_time())
        , price(val.get_price())
        , current_str()
        , queue_clients()
        , who_sits(number_of_tables, "")
        , occupancy_table(number_of_tables, {{}, {}}) {}

    uint16_t number_of_tables;
    hh_mm start_time;
    hh_mm end_time;
    uint32_t price;

    std::string current_str;
    std::vector<std::string> queue_clients;
    std::vector<std::string> who_sits;
    std::vector<hh_mm> occupancy_table;
};

void id11(hh_mm&, const std::string&);
void id12(club_info&, hh_mm&, std::string&, size_t);
void id13(hh_mm&, const std::string&);
void id1(club_info&, hh_mm&, std::string&);
void id2(club_info&, hh_mm&, std::string&, uint16_t);
void id3(club_info&, hh_mm&, std::string&);
void id4(club_info&, hh_mm&, std::string&);
void expel_clients_from_club(club_info&);

#endif  //COMPUTER_CLUB_FUNCS_FOR_ID_H
