#pragma once

#include <string>
#include <map>
#include <queue>

#include "filebuffer.hpp"
#include "mytime.hpp"


class ComputerClub
{
private:
    unsigned int tablesCount;
    Time openTime;
    Time closeTime;
    unsigned int costPerHour;

    FileBuffer buffer;

    std::queue<std::string> clientsQueue;
    std::map<std::string, unsigned int> tables;

public:
    ComputerClub() = delete;
    ComputerClub(const std::string& filename);

    void run();
};