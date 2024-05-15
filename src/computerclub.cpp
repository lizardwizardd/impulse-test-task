#include "../inc/computerclub.hpp" 

#include <iostream>
#include <exception>

#include "../inc/mytime.hpp"


ComputerClub::ComputerClub(const std::string& filename) :
    buffer(filename)
{
    buffer.readInputLine(); // считать количество столов
    tablesCount = std::stoi(buffer.getBuffer());

    buffer.readInputLine(); // считать время начала и конца работы
    std::string workTimeLine = buffer.getBuffer();
    openTime = Time(workTimeLine.substr(0, workTimeLine.find(' ')));
    closeTime = Time(workTimeLine.substr(workTimeLine.find(' '), workTimeLine.size()));

    buffer.readInputLine(); // считать стоимость часа
    costPerHour = std::stoi(buffer.getBuffer());
}

void ComputerClub::run()
{
    std::cout << tablesCount << " " << openTime << " " << closeTime << " " << costPerHour << '\n';

    while (buffer.readInputLine())
    {
        std::cout << buffer.getBuffer() << '\n';
    }
}