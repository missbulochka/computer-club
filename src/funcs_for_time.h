#ifndef COMPUTER_CLUB_FUNCS_FOR_TIME_H
#define COMPUTER_CLUB_FUNCS_FOR_TIME_H

#include "types.h"

hh_mm parse_time(const std::string&, char);
bool time_is_less_then(const hh_mm&, const hh_mm&);
void print_time(const hh_mm&, bool);


#endif // COMPUTER_CLUB_FUNCS_FOR_TIME_H
