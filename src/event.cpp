#include "../inc/event.hpp"

#include <sstream>

#include "../inc/myexceptions.hpp"

Event::Event(Time eventTime, TypeIn eventType, std::string clientName, unsigned int tableNumber) :
    eventTime(eventTime),
    eventType(eventType),
    clientName(clientName),
    tableNumber(tableNumber)
{}

Event::TypeIn Event::parseLine(const std::string& line)
{
    std::istringstream iss(line);
    try
    {
        std::string timeStr, typeStr, clientStr, tableStr;

        if (!(iss >> timeStr >> typeStr >> clientStr)) {
            throw ParseException("Invalid number of arguments", line);
        }

        this->eventTime = Time(timeStr);
        this->eventType = Event::TypeIn(std::stoi(typeStr));
        this->clientName = clientStr;

        if (iss >> tableStr) // в строке 4 аргумента
            this->tableNumber = std::stoi(tableStr);
        else                 // в строке 3 аргумента
            this->tableNumber = 0;

        return eventType;
    }
    catch (const std::exception& e)
    {
        throw ParseException(std::string(e.what()), line);
    }
}

Event::TypeIn Event::getEventType() const noexcept
{
    return eventType;
}

Time Event::getEventTime() const noexcept
{
    return eventTime;
}

std::string Event::getClientName() const noexcept
{
    return clientName;
}

unsigned int Event::getTableNumber() const noexcept
{
    return tableNumber;
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