#ifndef COMPUTER_CLUB_VALIDATION_H
#define COMPUTER_CLUB_VALIDATION_H

#include <string>
#include "types.h"

class validation {
public:
    explicit validation(std::string);

    uint16_t get_number_of_tables();
    hh_mm get_start_time();
    hh_mm get_end_time();
    uint32_t get_price();

private:
    std::string file;

    uint16_t number_of_tables;
    hh_mm start_time;
    hh_mm end_time;
    uint32_t price;

    std::string current_str;
    hh_mm last_time;

    void start_val();
    void error_msg(size_t);
    static bool only_digit(const std::string&);
    static bool only_alnum(const std::string&);
    bool only_time(const hh_mm&);
    static bool time_is_less_then(const hh_mm&, const hh_mm&);
};


#endif  //COMPUTER_CLUB_VALIDATION_H
