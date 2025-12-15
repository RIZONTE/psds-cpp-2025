#include <stdexcept>


struct Date {
    unsigned year;
    unsigned month;
    unsigned day;
};

struct StudentInfo {
    size_t id;
    char mark;
    int score;
    unsigned course;
    Date birth_date;
};