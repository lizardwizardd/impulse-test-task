#include "../inc/computerclub.hpp" 

#include <iostream>
#include <exception>

#include "../inc/mytime.hpp"
#include "../inc/eventin.hpp"
#include "../inc/eventout.hpp"


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
    std::cout << openTime << '\n';

    while (buffer.readInputLine())
    {
        try
        {
            EventIn eventIn(this, buffer.getBuffer());
            std::cout << eventIn << '\n';
            EventOut eventOut = eventIn.execute();
        }
        catch(const ParseException& e)
        {
            std::cout << "Error while parsing: " << e.what() << '\n'
                      << "Error line: " << e.getLine() << '\n';
        }
    }

    std::cout << closeTime << '\n';
}