#pragma once

#include "eventbase.hpp"

class EventOut : public EventBase
{
private:
    TypeOut eventType;

    void executeClientLeftEndOfDay() const;
    void executeClientOccupiedTableQueue() const;
    void executeError() const;

public:
    EventOut() = delete; // Для работы класса нужен указатель на ComputerClub
    EventOut(ComputerClub* computerClub, Time eventTime = Time(),
             TypeOut eventType = TypeOut::UNKNOWN);

    void execute();

    friend std::ostream& operator<<(std::ostream& out, const EventOut& event);
};