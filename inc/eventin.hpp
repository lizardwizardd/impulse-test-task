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
    EventIn() = delete; // Для работы класса нужен указатель на ComputerClub
    EventIn(ComputerClub* computerClub, Time eventTime = Time(), TypeIn eventType = TypeIn::UNKNOWN,
            std::string clientName = "", unsigned int tableNumber = 0);
    EventIn(ComputerClub* computerClub, const std::string& line);

    // Возвращает исходящее событие. Если в ответ на входящее событие
    // не должно быть исходящего, то возвращается событие с типом NO_EVENT
    EventOut execute();
    void parseLine(const std::string& line);
    TypeIn getType() const;

    friend std::ostream& operator<<(std::ostream& out, const EventIn& event);
};


class ParseException : public std::exception
{
private:
    std::string message;
    std::string line;

public:
    ParseException(const std::string& msg, const std::string& line);

    const char* what() const noexcept override;
    const std::string& getLine() const;
};