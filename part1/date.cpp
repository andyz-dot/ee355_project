#include "date.h"
#include <iostream>
#include <sstream>

using namespace std;

Date::Date() {
    month = 0;
    day = 0;
    year = 0;
}

Date::Date(string date_str) {
    set_date(date_str);
}

void Date::set_date(string date_str) {
    stringstream ss(date_str);
    char slash1, slash2;
    
    // '/' are extracted into slash1 and slash2
    // the input should be in the form of M/D/yyyy
    ss >> month >> slash1 >> day >> slash2 >> year;
}

void Date::print_date() {
    string month_names[13] = {
        "", "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    if (month >= 1 && month <= 12) {
        cout << month_names[month] << " " << day << ", " << year;
    } else {
        cout << "Invalid Date";
    }
}
