#pragma once

#include <string>
#include <iostream>


class Time
{
private:
    unsigned int mins = 0; // минуты с 00:00. Гарантировано значение от 0 до 24*60-1
    
public:
    Time(unsigned int time = 0);
    Time(const std::string& time); // получает на вход время в формате hh:mm

    void setTime(const std::string& time);
    void setMins(unsigned int time);
    unsigned int getMins() const;
    std::string getFormattedString() const;

    // Если левый аргумент меньше правого, предполагается что сменился день  
    Time operator-(const Time& time) const;

    bool operator==(const Time& time) const;

    friend std::ostream& operator<<(std::ostream& out, const Time& time);
};