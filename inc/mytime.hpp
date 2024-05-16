#pragma once

#include <string>
#include <iostream>

class Time
{
private:
    unsigned int mins = 0; // минуты с 00:00

public:
    Time(unsigned int time = 0);
    Time(const std::string& time); // получает на вход время в формате hh:mm

    // Если левый аргумент меньше правого, предполагается что сменился день  
    Time operator-(const Time& time) const;

    friend std::ostream& operator<<(std::ostream& out, const Time& time);
};