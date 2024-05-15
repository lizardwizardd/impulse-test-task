#include "../inc/mytime.hpp"

#include <iostream>
#include <iomanip>

Time::Time(const std::string& time)
{
    int hours = std::stoi(time.substr(0, time.find(':')));
    int minutes = std::stoi(time.substr(time.find(':') + 1, 2));

    mins = hours * 60 + minutes;
}

Time::Time(unsigned int time)
{
    mins = time;
}

Time Time::operator-(const Time& time) const
{
    if (mins > time.mins)
        return Time(mins - time.mins);
    else // прошел день
        return Time(24 * 60 + mins - time.mins);
}

std::ostream& operator<<(std::ostream& out, const Time& time)
{
    int hours = time.mins / 60;
    int minutes = time.mins % 60;
    out << std::setfill('0') << std::setw(2) << hours << ':' << std::setw(2) << minutes;

    return out;
}