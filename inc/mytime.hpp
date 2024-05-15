#pragma once

#include <string>
#include <iostream>

class Time
{
private:
    unsigned int mins; // минуты с 00:00

public:
    Time() = default;
    Time(unsigned int time);
    Time(const std::string& time); // получает на вход время в формате hh:mm

    // Если левый аргумент меньше правого, предполагается что сменился день  
    Time operator-(const Time& time) const;

    friend std::ostream& operator<<(std::ostream& out, const Time& time);
};