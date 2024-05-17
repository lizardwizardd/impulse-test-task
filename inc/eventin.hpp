#pragma once 

#include "eventbase.hpp"
#include "mytime.hpp"
#include "eventout.hpp"


class EventIn : public EventBase
{
private:
    TypeIn eventType;
    std::string clientName = "";
    unsigned int tableNumber = 0;

    TypeOut executeEntered() const;
    TypeOut executeOccupiedTable() const;
    TypeOut executeWaiting() const;
    TypeOut executeLeft() const;

public:
    EventIn() = delete; // Для работы класса обязателен указатель на ComputerClub
    EventIn(ComputerClub* computerClub, const std::string& line);
    EventIn(ComputerClub* computerClub, Time eventTime = Time(), TypeIn eventType = TypeIn::UNKNOWN,
            std::string clientName = "", unsigned int tableNumber = 0);

    // Возвращает исходящее событие. Если в ответ на входящее событие
    // не должно быть исходящего, то возвращается событие с типом NO_EVENT
    EventOut execute();
    TypeIn parseLine(const std::string& line); // считывает строку и возвращает тип события
    TypeIn getType() const;
    void print() const;

    friend std::ostream& operator<<(std::ostream& out, const EventIn& event);
};
