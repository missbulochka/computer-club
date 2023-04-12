#ifndef COMPUTER_CLUB_VALIDATION_H
#define COMPUTER_CLUB_VALIDATION_H

#include "funcs_for_time.h"

class validation {
public:
    explicit validation(std::string);

    uint16_t get_number_of_tables() const;
    hh_mm get_start_time();
    hh_mm get_end_time();
    uint32_t get_price() const;

private:
    std::string file;

    uint16_t number_of_tables;
    hh_mm start_time;
    hh_mm end_time;
    uint32_t price;

    std::string current_str;
    hh_mm last_time;

    void start_val();
    static bool only_digit(const std::string&);
    static bool only_alnum(const std::string&);
    static bool only_time(const hh_mm&);

    void table_or_price_val();
    void time_val();
    void event_val(size_t&);
};


#endif  //COMPUTER_CLUB_VALIDATION_H
