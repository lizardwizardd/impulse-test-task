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

    std::queue<std::string> clientsQueue;
    std::map<std::string, unsigned int> tables;

public:
    ComputerClub() = delete;
    ComputerClub(const std::string& filename);
    ~ComputerClub();

    void run();
};