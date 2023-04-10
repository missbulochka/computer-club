#ifndef COMPUTER_CLUB_VALIDATION_H
#define COMPUTER_CLUB_VALIDATION_H

#include <string>

class validation {
public:
    explicit validation(std::string);

    uint16_t get_number_of_tables();
    std::pair<std::string, std::string> get_start_time();
    std::pair<std::string, std::string> get_end_time();
    uint32_t get_price();

private:
    std::string file;

    uint16_t number_of_tables;
    std::pair<std::string, std::string> start_time;
    std::pair<std::string, std::string> end_time;
    uint32_t price;

    std::string current_str;
    std::pair<std::string, std::string> last_time;

    void start_val();
    void error_msg(size_t);
    static bool only_digit(const std::string&);
    static bool only_alnum(const std::string&);
    bool time_validation(const std::pair<std::string, std::string>&);
    static bool time_is_less_then(const std::pair<std::string, std::string>&, const std::pair<std::string, std::string>&);
    static std::pair<std::string, std::string> parse_time(const std::string&, char);
};


#endif  //COMPUTER_CLUB_VALIDATION_H
