#pragma once

#include <string>

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

public:
    ComputerClub() = delete;
    ComputerClub(const std::string& filename);

    void run();
};