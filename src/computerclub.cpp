#include "../inc/computerclub.hpp" 

#include <iostream>
#include <exception>

#include "../inc/mytime.hpp"
#include "../inc/eventin.hpp"
#include "../inc/eventout.hpp"
#include "../inc/myexceptions.hpp"


ComputerClub::ComputerClub(const std::string& filename) :
    file(filename), buffer(file)
{
    if (!file.is_open())
    {
        throw std::runtime_error("Error opening file '" + filename + "'. \n" +
                                 "Make sure the specified path is correct.");
    }

    try
    {
        buffer.readInputLine(); // количество столов
        tablesCount = std::stoi(buffer.getBuffer());

        buffer.readInputLine(); // время начала и конца работы
        std::string workTimeLine = buffer.getBuffer();
        openTime = Time(workTimeLine.substr(0, workTimeLine.find(' ')));
        closeTime = Time(workTimeLine.substr(workTimeLine.find(' ') + 1, workTimeLine.size()));

        buffer.readInputLine(); // стоимость часа
        costPerHour = std::stoi(buffer.getBuffer());
    }
    catch(const std::exception& e)
    {
        std::cout << "Error while parsing: " << e.what() << '\n'
                  << "Error line: " << buffer.getBuffer() << '\n';
    }
}

ComputerClub::~ComputerClub()
{
    file.close();
}

void ComputerClub::run()
{
    std::cout << openTime << '\n';

    while (buffer.readInputLine())
    {
        EventIn eventIn(this);
        
        try {
            eventIn.parseLine(buffer.getBuffer());
        } catch(const ParseException& e) {
            std::cout << "Error while parsing: " << e.what() << '\n'
                      << "Error line: "          << e.getLine() << '\n';
        }

        EventOut eventOut = eventIn.execute();
        eventIn.print();

        if (eventOut.needToExecute())
        {
            eventOut.execute();
            eventOut.print();
        }
    }

    std::cout << closeTime << '\n';
}