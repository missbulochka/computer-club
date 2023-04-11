#include "funcs_for_time.h"

hh_mm parse_time(const std::string& str, char sep) {
    auto sep_pos = str.find(sep);
    auto block_1 = str.substr(0, sep_pos);
    auto block_2 = str.substr(sep_pos + 1);

    return {block_1, block_2};
}
