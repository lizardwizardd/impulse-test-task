#pragma once

#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <deque>

#include "inputbuffer.hpp"
#include "event.hpp"
#include "mytime.hpp"


struct Client
{
    std::string name = "";
    unsigned int tableNumber = 0;

    Client() = default;
    Client(const std::string& name, unsigned int tableNumber = 0);
};


class Table
{
private:
    bool isOccupiedState = false;
    Client currentClient;
    Time startTime; // время когда currentClient занял стол
    unsigned int revenue = 0;
    unsigned int totalMins = 0; // сколько минут был занят стол за день

public:
    static unsigned int costPerHour;

    unsigned int getRevenue() const;
    unsigned int getTotalMins() const;
    bool isOccupied() const;

    // Освободить стол и подсчитать доход. Не изменяет client.tableNumber
    void clientLeaves(const Time& time);

    // На вход поступает клиент, не занимающий стол. После вызова функции, 
    // client.tableNumber должно быть изменено на соответствующее значение
    void clientOccupies(const Client& client, const Time& time);
};


// Хранит информацию о состоянии компьютерного клуба
class ComputerClub
{
private:
    unsigned int tablesCount; // количество столов в клубе
    Time openTime;
    Time closeTime;
    unsigned int costPerHour;

    std::ifstream file;
    InputBuffer buffer;

    std::vector<Table> tables;             // все столы; нумерация с 1
    std::map<std::string, Client> clients; // все клиенты
    std::deque<std::string> clientsQueue;  // клиенты в очереди

    // Обрабатывает входящее событие. Возвращает тип исходящего события.
    // event может быть изменен в результате обработки
    Event::TypeOut handleEventIn(Event& event);

    Event::TypeOut handleClientEntered(const Event& event);
    Event::TypeOut handleClientOccupiedTable(const Event& event);
    Event::TypeOut handleClientWaiting(const Event& event);
    Event::TypeOut handleClientLeft(Event& event); // может изменить event

    // На вход поступает событие с clientName из очереди
    void occupyFromQueue(const Event& eventIn);
    void clientLeaveQueueTooLong(Event& event); // изменяет event
    void printError(const Time& time, const std::string& errorText);

    void endOfDayAllClientsLeave(const Time& time);
    void printTablesStats();

    bool isOpen(const Time& time);

public:
    ComputerClub() = delete;
    ComputerClub(const std::string& filename);
    ~ComputerClub();

    void run();
};