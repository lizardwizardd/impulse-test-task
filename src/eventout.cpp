#include "../inc/eventout.hpp"

EventOut::EventOut(ComputerClub* computerClub, Time time, TypeOut type) :
    EventBase(computerClub, time),
    eventType(type)
{}

void EventOut::execute()
{
    switch (eventType)
    {
        case TypeOut::NO_EVENT:
            break;
        case TypeOut::CLIENT_LEFT_END_OF_DAY:
            executeClientLeftEndOfDay();
            break;
        case TypeOut::CLIENT_OCCUPIED_TABLE_QUEUE:
            executeClientOccupiedTableQueue();
            break;
        case TypeOut::ERROR:
            executeError();
            break;
        default:
            throw std::runtime_error("Unknown event type in execute()");
    }
}

void EventOut::executeClientLeftEndOfDay() const
{

}

void EventOut::executeClientOccupiedTableQueue() const
{

}

void EventOut::executeError() const
{
    
}

std::ostream& operator<<(std::ostream& out, const EventOut& event)
{
    out << event.eventTime << " " << (unsigned int)event.eventType;
    return out;
}