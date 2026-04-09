#ifndef DATE_H
#define DATE_H

#include <string>

using namespace std;

class Date {
private:
    int month;
    int day;
    int year;

public:
    Date();
    //overloaded constructor
    Date(string date_str);
    //setter to parse and store the date string
    void set_date(string date_str);
    //prints the date
    void print_date();
};
#endif
