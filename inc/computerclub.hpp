#pragma once

#include <string>
#include <map>
#include <fstream>
#include <queue>

#include "inputbuffer.hpp"
#include "event.hpp"
#include "mytime.hpp"


class Client
{
public:
    std::string name;
    Time startTime;

    Client() = default;
    Client(const std::string& name, const Time& startTime = Time());
};


class Table
{
public:
    bool isOccupied = false;
    Time currentClient;
    Time startTime;
    unsigned int revenue = 0;
    unsigned int occupiedMinutes = 0;
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

    std::vector<Table> tables;             // все столы
    std::map<std::string, Client> clients; // все клиенты
    std::queue<std::string> clientsQueue;  // клиенты в очереди

    // Обрабатывает входящее событие. Возвращает тип исходящего события
    Event::Type handleEventIn(const Event& event);

    Event::Type handleClientEntered(const Event& event);
    Event::Type handleClientOccupiedTable(const Event& event);
    Event::Type handleClientWaiting(const Event& event);
    Event::Type handleClientLeft(const Event& event);

    void printError(const std::string& errorText);

public:
    ComputerClub() = delete;
    ComputerClub(const std::string& filename);
    ~ComputerClub();

    void run();
};