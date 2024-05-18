#include "../inc/mytime.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>

#include "../inc/myexceptions.hpp"

Time::Time(const std::string& time)
{
    setTime(time);
}

Time::Time(unsigned int time)
{
    setMins(time);
}

void Time::setTime(const std::string& time)
{
    // Проверить формат строки
    if (time.size() != 5 || time[2] != ':')
        throw std::invalid_argument("Invalid time format. Format: hh:mm");

    int hours;
    int minutes;
    try
    {
        hours = std::stoi(time.substr(0, 2));
        minutes = std::stoi(time.substr(3, 2));
    }
    catch(...)
    {
        throw std::invalid_argument("std::stoi error while parsing time");
    }

    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59)
        throw std::invalid_argument("Time must be between 00:00 and 23:59");

    mins = hours * 60 + minutes;
}

void Time::setMins(unsigned int time)
{
    if (time < 0 || time > 24 * 60)
        throw std::invalid_argument("Time must be between 00:00 and 23:59");

    mins = time;
}

unsigned int Time::getMins() const
{
    return mins;
}

std::string Time::getFormattedString() const
{
    std::stringstream ss;
    int hours = mins / 60;
    int minutes = mins % 60;
    ss << std::setfill('0') << std::setw(2) << hours << ':' << std::setw(2) << minutes;

    return ss.str();
}

// Если левый аргумент меньше правого, предполагается что сменился день  
Time Time::operator-(const Time& time) const
{
    if (mins >= time.mins)
        return Time(mins - time.mins);
    else // прошел день
        return Time(24 * 60 + mins - time.mins);
}

bool Time::operator==(const Time& time) const
{
    return mins == time.mins;
}

std::ostream& operator<<(std::ostream& out, const Time& time)
{
    out << time.getFormattedString();

    return out;
}