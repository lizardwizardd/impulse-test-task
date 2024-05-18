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


struct Table
{
    static unsigned int costPerHour;

    bool isOccupied = false;
    Client currentClient;
    Time startTime; // время когда currentClient занял стол
    unsigned int revenue = 0;

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
    unsigned int tablesCount;
    Time openTime;
    Time closeTime;
    unsigned int costPerHour;

    std::ifstream file;
    InputBuffer buffer;

    std::vector<Table> tables;             // все столы; нумерация с 1
    std::map<std::string, Client> clients; // все клиенты
    std::deque<std::string> clientsQueue;  // клиенты в очереди

    // Обрабатывает входящее событие. Возвращает тип исходящего события
    Event::Type handleEventIn(const Event& event);

    Event::Type handleClientEntered(const Event& event);
    Event::Type handleClientOccupiedTable(const Event& event);
    Event::Type handleClientWaiting(const Event& event);
    Event::Type handleClientLeft(const Event& event);

    void printError(const Time& time, const std::string& errorText);

    bool isOpen(const Time& time);

public:
    ComputerClub() = delete;
    ComputerClub(const std::string& filename);
    ~ComputerClub();

    void run();
};