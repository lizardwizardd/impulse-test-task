#pragma once

#include <string>
#include <map>
#include <fstream>
#include <queue>

#include "inputbuffer.hpp"
#include "mytime.hpp"


class ComputerClub
{
private:
    unsigned int tablesCount;
    Time openTime;
    Time closeTime;
    unsigned int costPerHour;

    std::ifstream file;
    InputBuffer buffer;

    struct Client {
        std::string name;
        Time startTime;
    };

    struct Table {
        bool isOccupied = false;
        Time currentClient;
        Time startTime;
        unsigned int revenue = 0;
        unsigned int occupiedMinutes = 0;
    };

    std::vector<Table> tables;             // все столы
    std::map<std::string, Client> clients; // все клиенты
    std::queue<std::string> clientsQueue;  // клиенты в очереди

public:
    ComputerClub() = delete;
    ComputerClub(const std::string& filename);
    ~ComputerClub();

    void run();
};