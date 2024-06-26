#include "../inc/computerclub.hpp" 

#include <iostream>
#include <exception>
#include <deque>
#include <string> 

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

bool Table::isOccupied() const
{
    return isOccupiedState;
}

unsigned int Table::getRevenue() const
{
    return revenue;
}

unsigned int Table::getTotalMins() const
{
    return totalMins;
}

void Table::clientLeaves(const Time& time)
{
    if (!isOccupied())
        throw std::logic_error("Can't leave an empty table.");

    unsigned int minsOccupied = Time(time - startTime).getMins();
    revenue += ((minsOccupied + 59) / 60) * Table::costPerHour;
    totalMins += minsOccupied;

    isOccupiedState = false;
    currentClient = Client();
    startTime = Time();
}

void Table::clientOccupies(const Client& client, const Time& time)
{
    if (isOccupied())
        throw std::logic_error("Can't occupy a non-empty table.");

    if (client.tableNumber != 0)
        throw std::logic_error("Client already occupies a table.");

    isOccupiedState = true;
    currentClient = client;
    startTime = time;
}

//
// COMPUTER CLUB
//

ComputerClub::ComputerClub(std::istream& inputStream) :
    buffer(inputStream)
{
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
            case Event::TypeOut::SUCCESS_NO_EVENT:
                break;
            case Event::TypeOut::TABLE_FREE_QUEUE_NOT_EMPTY:
                occupyFromQueue(event);
                event.print();
                break;
            case Event::TypeOut::CLIENT_LEFT_FORCED:
                clientLeaveQueueTooLong(event);
                event.print();
                break;
            case Event::TypeOut::ERROR_CLIENT_ALREADY_INSIDE:
                printError(event.getEventTime(), "YouShallNotPass");
                break;
            case Event::TypeOut::ERROR_NOT_OPEN_YET:
                printError(event.getEventTime(), "NotOpenYet");
                break;
            case Event::TypeOut::ERROR_PLACE_IS_BUSY:
                printError(event.getEventTime(), "PlaceIsBusy");
                break;
            case Event::TypeOut::ERROR_CLIENT_UNKNOWN:
                printError(event.getEventTime(), "ClientUnknown");
                break;
            case Event::TypeOut::ERROR_CLIENT_CAN_NOT_WAIT:
                printError(event.getEventTime(), "ICanWainNoLonger!");
                break;
            case Event::TypeOut::UNKNOWN:
                throw std::runtime_error("Unknown outgoing event type");
            default:
                throw std::runtime_error("Unexpected outgoing event type");
        }        
    }

    endOfDayAllClientsLeave(closeTime);
    std::cout << closeTime << '\n';
    printTablesStats();
}


Event::TypeOut ComputerClub::handleEventIn(Event& event)
{
    switch (event.getEventType())
    {
        case Event::TypeIn::CLIENT_ENTERED:
            return handleClientEntered(event);
        case Event::TypeIn::CLIENT_OCCUPIED_TABLE:
            return handleClientOccupiedTable(event);
        case Event::TypeIn::CLIENT_WAITING:
            return handleClientWaiting(event);
        case Event::TypeIn::CLIENT_LEFT:
            return handleClientLeft(event);
        default:
            throw std::runtime_error("Unknown incoming event type");
    }
}


Event::TypeOut ComputerClub::handleClientEntered(const Event& event)
{
    if (clients.find(event.getClientName()) != clients.end())
        return Event::TypeOut::ERROR_CLIENT_ALREADY_INSIDE;

    if (!isOpen(event.getEventTime()))
        return Event::TypeOut::ERROR_NOT_OPEN_YET;

    clients.insert({ event.getClientName(), Client(event.getClientName()) });

    return Event::TypeOut::SUCCESS_NO_EVENT;
}

Event::TypeOut ComputerClub::handleClientOccupiedTable(const Event& event)
{
    if (event.getTableNumber() > tablesCount || event.getTableNumber() < 1)
        throw ParseException("Table number out of range", buffer.getBuffer());

    if (clients.find(event.getClientName()) == clients.end())
        return Event::TypeOut::ERROR_CLIENT_UNKNOWN;

    if (tables[event.getTableNumber()].isOccupied())
        return Event::TypeOut::ERROR_PLACE_IS_BUSY;

    Client& client = clients.at(event.getClientName());

    // Освободить стол, если клиент пересаживается
    if (client.tableNumber != 0)
    {
        tables[client.tableNumber].clientLeaves(event.getEventTime());
    }

    // Занять стол
    tables[event.getTableNumber()].clientOccupies(client, event.getEventTime());
    client.tableNumber = event.getTableNumber();

    return Event::TypeOut::SUCCESS_NO_EVENT;
}

Event::TypeOut ComputerClub::handleClientWaiting(const Event& event)
{
    if (clients.find(event.getClientName()) == clients.end())
        return Event::TypeOut::ERROR_CLIENT_UNKNOWN;
    
    if (clients.at(event.getClientName()).tableNumber != 0)
        throw std::logic_error("Client can't wait because he already occupies a table");

    if (clientsQueue.size() > tablesCount)
    {
        return Event::TypeOut::CLIENT_LEFT_FORCED;
    }

    // Проверить, если ли свободный стол
    for (unsigned int i = 1; i < tables.size(); i++)
    {
        if (!tables[i].isOccupied())
            return Event::TypeOut::ERROR_CLIENT_CAN_NOT_WAIT;
    }

    // Добавить в очередь
    clientsQueue.push_back(event.getClientName());

    return Event::TypeOut::SUCCESS_NO_EVENT;
}

Event::TypeOut ComputerClub::handleClientLeft(Event& event)
{
    if (clients.find(event.getClientName()) == clients.end())
        return Event::TypeOut::ERROR_CLIENT_UNKNOWN;

    // Освободить стол или очередь.
    unsigned int freeTableIndex = clients.at(event.getClientName()).tableNumber;

    if (freeTableIndex != 0)
    {
        tables[freeTableIndex].clientLeaves(event.getEventTime());
    }
    else // клент не зангимал стол. Удалить из очереди, если он есть в ней
    {
        for (auto it = clientsQueue.begin(); it != clientsQueue.end(); it++)
        {
            if (*it == event.getClientName())
            {
                clientsQueue.erase(it);
                break;
            }
        }
    }

    clients.erase(event.getClientName());

    // Если очередь пустая, или не освободился стол
    if (clientsQueue.size() == 0 || freeTableIndex == 0)
    {
        return Event::TypeOut::SUCCESS_NO_EVENT;
    }
    else
    {
        // Изменить event, чтобы упростить его обработку в occupyFromQueue и вывод в cout
        event = Event(event.getEventTime(), Event::TypeIn::TABLE_FREE_QUEUE_NOT_EMPTY,
                      clientsQueue.front(), freeTableIndex);
        return Event::TypeOut::TABLE_FREE_QUEUE_NOT_EMPTY;
    }
}


void ComputerClub::occupyFromQueue(const Event& eventIn)
{
    if (clientsQueue.size() == 0)
        throw std::logic_error("Clients queue is empty");
    
    std::string clientName = eventIn.getClientName();

    // Занять освободившийся стол
    Client& client = clients.at(clientName);
    tables[eventIn.getTableNumber()].clientOccupies(client, eventIn.getEventTime());
    client.tableNumber = eventIn.getTableNumber();

    clientsQueue.pop_front();
}

void ComputerClub::clientLeaveQueueTooLong(Event& event)
{
    if (clients.find(event.getClientName()) == clients.end())
        throw std::invalid_argument("Name of client to leave not found");

    Client& client = clients.at(event.getClientName());
    if (client.tableNumber != 0) // нужно освободить стол
    {
        tables[client.tableNumber].clientLeaves(event.getEventTime());
        client.tableNumber = 0;
    }

    clients.erase(event.getClientName());

    event = Event(event.getEventTime(), Event::TypeIn::CLIENT_LEFT_FORCED, event.getClientName());
}

void ComputerClub::endOfDayAllClientsLeave(const Time& time)
{
    for (auto& client : clients)
    {
        if (client.second.tableNumber != 0)
        {
            tables[client.second.tableNumber].clientLeaves(time);
            client.second.tableNumber = 0;
        }

        std::cout << time << " " << (unsigned int)Event::TypeOut::CLIENT_LEFT_FORCED
                  << " "  << client.first << '\n';
    }
}

void ComputerClub::printTablesStats()
{
    for (unsigned int i = 1; i < tables.size(); i++)
    {
        std::cout << i << " " << tables[i].getRevenue() << " " << Time(tables[i].getTotalMins()) << '\n';
    }
}

void ComputerClub::printError(const Time& time, const std::string& errorText)
{
    std::cout << time << " " << (unsigned int)Event::TypeOut::ERROR << " " << errorText << '\n';
}

bool ComputerClub::isOpen(const Time& time)
{
    if (openTime > closeTime) // во время работы проходит день
        return time >= openTime || time <= closeTime;
    else
        return time >= openTime && time <= closeTime;
}