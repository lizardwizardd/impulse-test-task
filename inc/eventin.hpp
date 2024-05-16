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
    EventIn() = delete;
    EventIn(ComputerClub* computerClub, Time eventTime = Time(), TypeIn eventType = TypeIn::UNKNOWN,
            std::string clientName = "", unsigned int tableNumber = 0);
    EventIn(ComputerClub* computerClub, const std::string& line);

    EventOut execute();
    void parseLine(const std::string& line);

    friend std::ostream& operator<<(std::ostream& out, const EventIn& event);
};