#include "../inc/event.hpp"

#include "../inc/myexceptions.hpp"

Event::Event(Time eventTime, Type eventType, std::string clientName, unsigned int tableNumber) :
    eventTime(eventTime),
    eventType(eventType),
    clientName(clientName),
    tableNumber(tableNumber)
{}

Event::Type Event::parseLine(const std::string& line)
{
    try
    {
        size_t firstSpaceI = line.find(' ');
        size_t secondSpaceI = line.find(' ', firstSpaceI + 1);
        size_t thirdSpaceI = line.find(' ', secondSpaceI + 1);

        this->eventTime = Time(line.substr(0, firstSpaceI));
        this->eventType = Event::Type(std::stoi(line.substr(firstSpaceI + 1, secondSpaceI - firstSpaceI - 1)));

        if (thirdSpaceI == std::string::npos) // в строке 3 аргумента
            this->clientName = line.substr(secondSpaceI + 1, line.size() - secondSpaceI - 1);
        else                                  // в строке 4 аргумента
        {
            this->clientName = line.substr(secondSpaceI + 1, thirdSpaceI - secondSpaceI - 1);
            this->tableNumber = std::stoi(line.substr(thirdSpaceI + 1, line.size() - thirdSpaceI - 1));
        }

        return eventType;
    }
    catch(const std::exception& e)
    {
        throw ParseException(std::string(e.what()), line);
    }
}

Event::Type Event::getEventType() const noexcept
{
    return eventType;
}

Time Event::getEventTime() const noexcept
{
    return eventTime;
}

void Event::print() const
{
    if (tableNumber == 0) // в строке 3 аргумента
    {
        std::cout << eventTime  << " " << (unsigned int)eventType << " "
                  << clientName << "\n";
    }
    else // в строке 4 аргумента 
    {
        std::cout << eventTime  << " " << (unsigned int)eventType << " "
                  << clientName << " " << tableNumber << "\n";
    }
}