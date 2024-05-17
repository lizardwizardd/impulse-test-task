#include "../inc/eventin.hpp"

EventIn::EventIn(ComputerClub* computerClub, const std::string& line) :
    EventBase(computerClub, Time())
{
    parseLine(line);
}

EventIn::EventIn(ComputerClub* computerClub, Time time, TypeIn type,
                 std::string clientName, unsigned int tableNumber) :
    EventBase(computerClub, time),
    eventType(type),
    clientName(clientName),
    tableNumber(tableNumber)
{}

void EventIn::parseLine(const std::string& line)
{
    try
    {
        size_t firstSpaceI = line.find(' ');
        size_t secondSpaceI = line.find(' ', firstSpaceI + 1);
        size_t thirdSpaceI = line.find(' ', secondSpaceI + 1);

        this->eventTime = Time(line.substr(0, firstSpaceI));
        this->eventType = EventIn::TypeIn(std::stoi(line.substr(firstSpaceI + 1, secondSpaceI - firstSpaceI - 1)));

        if (thirdSpaceI == std::string::npos) // в строке 3 аргумента
            this->clientName = line.substr(secondSpaceI + 1, line.size() - secondSpaceI - 1);
        else                                  // в строке 4 аргумента
        {
            this->clientName = line.substr(secondSpaceI + 1, thirdSpaceI - secondSpaceI - 1);
            this->tableNumber = std::stoi(line.substr(thirdSpaceI + 1, line.size() - thirdSpaceI - 1));
        }
    }
    catch(const std::exception& e)
    {
        throw ParseException(std::string(e.what()), line);
    }
}

EventOut EventIn::execute()
{
    switch (eventType)
    {
        case EventIn::TypeIn::CLIENT_ENTERED:
            return EventOut(computerClub, eventTime, executeEntered());
        case EventIn::TypeIn::CLINET_OCCUPIED_TABLE:
            return EventOut(computerClub, eventTime, executeOccupiedTable());
        case EventIn::TypeIn::CLIENT_WAITING:
            return EventOut(computerClub, eventTime, executeWaiting());
        case EventIn::TypeIn::CLIENT_LEFT:
            return EventOut(computerClub, eventTime, executeLeft());
        default:
            throw std::runtime_error("Unknown event type in execute()");
    }
}

EventIn::TypeIn EventIn::getType() const
{
    return eventType;
}

EventIn::TypeOut EventIn::executeEntered() const
{
    return EventIn::TypeOut::UNKNOWN;
}

EventIn::TypeOut EventIn::executeOccupiedTable() const
{
    return EventIn::TypeOut::UNKNOWN;
}

EventIn::TypeOut EventIn::executeWaiting() const
{
    return EventIn::TypeOut::UNKNOWN;
}

EventIn::TypeOut EventIn::executeLeft() const
{
    return EventIn::TypeOut::UNKNOWN;
}

std::ostream& operator<<(std::ostream& out, const EventIn& event)
{
    if (event.tableNumber == 0) // в строке 3 аргумента
    {
        out << event.eventTime << " " << (unsigned int)event.eventType << " "
            << event.clientName;
    }
    else // в строке 4 аргумента 
    {
        out << event.eventTime  << " " << (unsigned int)event.eventType << " "
            << event.clientName << " " << event.tableNumber;
    }
    return out;
}

//
// PARSE EXCEPTION
//

ParseException::ParseException(const std::string& msg, const std::string& line) :
    message(msg),
    line(line)
{}

const char* ParseException::what() const noexcept
{
    return message.c_str();
}

const std::string& ParseException::getLine() const
{
    return line;
}