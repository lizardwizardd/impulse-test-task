#include "../inc/computerclub.hpp" 

#include <iostream>
#include <exception>

#include "../inc/mytime.hpp"
#include "../inc/event.hpp"
#include "../inc/myexceptions.hpp"


//
// CLIENT
//

Client::Client(const std::string& name, unsigned int tableNumber) :
    name(name),
    tableNumber(tableNumber)
{}

//
// TABLE
//

unsigned int Table::costPerHour = 0;

void Table::clientLeaves(const Time& time)
{
    if (!isOccupied)
        throw std::logic_error("Can't leave an empty table.");

    unsigned int minsOccupied = Time(time - startTime).getMins();
    revenue += ((minsOccupied + 59) / 60) * Table::costPerHour;

    isOccupied = false;
    currentClient = Client();
    startTime = Time();
}

void Table::clientOccupies(const Client& client, const Time& time)
{
    if (isOccupied)
        throw std::logic_error("Can't occupy a non-empty table.");

    if (client.tableNumber != 0)
        throw std::logic_error("Client already occupies a table.");

    isOccupied = true;
    currentClient = client;
    startTime = time;
}

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

    Table::costPerHour = costPerHour;
    tables.resize(tablesCount + 1);
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
            case Event::Type::SUCCESS_NO_EVENT:
                break;
            case Event::Type::FREE_TABLE_QUEUE_NOT_EMPTY:
                break;
            case Event::Type::ERROR_CLIENT_ALREADY_INSIDE:
                printError(event.getEventTime(), "YouShallNotPass");
                break;
            case Event::Type::ERROR_NOT_OPEN_YET:
                printError(event.getEventTime(), "NotOpenYet");
                break;
            case Event::Type::ERROR_PLACE_IS_BUSY:
                printError(event.getEventTime(), "PlaceIsBusy");
                break;
            case Event::Type::ERROR_CLIENT_UNKNOWN:
                printError(event.getEventTime(), "ClientUnknown");
                break;
            case Event::Type::ERROR_CLIENT_CAN_NOT_WAIT:
                printError(event.getEventTime(), "ICanWainNoLonger!");
                break;
            case Event::Type::UNKNOWN:
                throw std::runtime_error("Unknown outgoing event type");
            default:
                throw std::runtime_error("Unexpected outgoing event type");
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
        case Event::Type::CLIENT_OCCUPIED_TABLE:
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
    if (clients.find(event.getClientName()) != clients.end())
        return Event::Type::ERROR_CLIENT_ALREADY_INSIDE;

    if (!isOpen(event.getEventTime()))
        return Event::Type::ERROR_NOT_OPEN_YET;

    clients.insert({ event.getClientName(), Client(event.getClientName()) });

    return Event::Type::SUCCESS_NO_EVENT;
}

Event::Type ComputerClub::handleClientOccupiedTable(const Event& event)
{
    if (clients.find(event.getClientName()) == clients.end())
        return Event::Type::ERROR_CLIENT_UNKNOWN;

    if (tables[event.getTableNumber()].isOccupied)
        return Event::Type::ERROR_PLACE_IS_BUSY;

    Client& client = clients.at(event.getClientName());

    // Освободить стол, если клиент пересаживается
    if (client.tableNumber != 0)
    {
        tables[client.tableNumber].clientLeaves(event.getEventTime());
    }

    // Занять стол
    tables[event.getTableNumber()].clientOccupies(client, event.getEventTime());
    client.tableNumber = event.getTableNumber();

    return Event::Type::SUCCESS_NO_EVENT;
}

Event::Type ComputerClub::handleClientWaiting(const Event& event)
{
    if (clients.find(event.getClientName()) == clients.end())
        return Event::Type::ERROR_CLIENT_UNKNOWN;
    
    if (clientsQueue.size() > tablesCount)
    {
        return Event::Type::CLIENT_LEFT_END_OF_DAY;
    }

    // Проверить, если ли свободный стол
    for (unsigned int i = 1; i < tablesCount; i++)
    {
        if (!tables[i].isOccupied)
            return Event::Type::ERROR_CLIENT_CAN_NOT_WAIT;
    }

    // Добавить в очередь
    clientsQueue.push_back(event.getClientName());

    return Event::Type::SUCCESS_NO_EVENT;
}

Event::Type ComputerClub::handleClientLeft(const Event& event)
{
    if (clients.find(event.getClientName()) == clients.end())
        return Event::Type::ERROR_CLIENT_UNKNOWN;

    // Освободить стол
    if (clients.at(event.getClientName()).tableNumber != 0)
    {
        tables[clients.at(event.getClientName()).tableNumber].clientLeaves(event.getEventTime());
    }

    // Удалить из clients
    clients.erase(event.getClientName());

    if (clientsQueue.size() == 0)
    {
        return Event::Type::SUCCESS_NO_EVENT;
    }
    else
    {
        return Event::Type::FREE_TABLE_QUEUE_NOT_EMPTY;
    }
}

void ComputerClub::printError(const Time& time, const std::string& errorText)
{
    std::cout << time << " " << (unsigned int)Event::Type::ERROR << " " << errorText << '\n';
}

bool ComputerClub::isOpen(const Time& time)
{
    if (openTime > closeTime) // во время работы проходит день
        return time >= openTime || time <= closeTime;
    else
        return time >= openTime && time <= closeTime;
}