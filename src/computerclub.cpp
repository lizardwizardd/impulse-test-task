#include "../inc/computerclub.hpp" 

#include <iostream>
#include <exception>

#include "../inc/mytime.hpp"
#include "../inc/event.hpp"
#include "../inc/myexceptions.hpp"


//
// CLIENT
//

Client::Client(const std::string& name, const Time& startTime) :
    name(name),
    startTime(startTime)
{}

//
// COMPUTER CLUB
//

ComputerClub::ComputerClub(const std::string& filename) :
    file(filename),
    buffer(file)
{
    if (!file.is_open())
    {
        throw std::runtime_error("Error opening file '" + filename + "'. \n" +
                                 "Make sure the specified path is correct.");
    }

    try
    {
        buffer.readInputLine(); // количество столов
        tablesCount = std::stoi(buffer.getBuffer());

        buffer.readInputLine(); // время начала и конца работы
        std::string workTimeLine = buffer.getBuffer();
        openTime = Time(workTimeLine.substr(0, workTimeLine.find(' ')));
        closeTime = Time(workTimeLine.substr(workTimeLine.find(' ') + 1, 5));

        buffer.readInputLine(); // стоимость часа
        costPerHour = std::stoi(buffer.getBuffer());
    }
    catch(const std::exception& e)
    {
        throw ParseException(std::string(e.what()), buffer.getBuffer());
    }
}

ComputerClub::~ComputerClub()
{
    file.close();
}

void ComputerClub::run()
{
    std::cout << openTime << '\n';

    while (buffer.readInputLine())
    {
        Event event;
        event.parseLine(buffer.getBuffer());
        event.print();

        switch (handleEventIn(event))
        {
            case Event::Type::NO_EVENT:
                break;
            case Event::Type::CLIENT_OCCUPIED_TABLE_QUEUE:
                break;
            case Event::Type::ERROR:
                printError(buffer.getBuffer());
                break;
            default:
                throw std::runtime_error("Unknown outgoing event type");
        }        
    }

    std::cout << closeTime << '\n';
}


Event::Type ComputerClub::handleEventIn(const Event& event)
{
    switch (event.getEventType())
    {
        case Event::Type::CLIENT_ENTERED:
            return handleClientEntered(event);
        case Event::Type::CLINET_OCCUPIED_TABLE:
            return handleClientOccupiedTable(event);
        case Event::Type::CLIENT_WAITING:
            return handleClientWaiting(event);
        case Event::Type::CLIENT_LEFT:
            return handleClientLeft(event);
        default:
            throw std::runtime_error("Unknown incoming event type");
    }
}


Event::Type ComputerClub::handleClientEntered(const Event& event)
{
    return Event::Type::NO_EVENT;
}

Event::Type ComputerClub::handleClientOccupiedTable(const Event& event)
{
    return Event::Type::NO_EVENT;
}

Event::Type ComputerClub::handleClientWaiting(const Event& event)
{
    return Event::Type::NO_EVENT;
}

Event::Type ComputerClub::handleClientLeft(const Event& event)
{
    return Event::Type::NO_EVENT;
}

void ComputerClub::printError(const std::string& errorText)
{
    std::cout << errorText << '\n';
}