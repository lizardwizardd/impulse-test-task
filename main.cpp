#include <iostream>

#include "inc/computerclub.hpp"
#include "inc/myexceptions.hpp"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "File name not specified\n";
        return 1;
    }

    std::string filename = argv[1];
    // std::string filename = "../../sample_input2.txt";

    try
    {
        std::ifstream inputFile(filename);
        if (!inputFile.is_open())
            throw std::runtime_error("Error opening file '" + filename + "'.");

        ComputerClub computerClub(inputFile);
        computerClub.run();
    }
    catch(const ParseException& e)
    {
        std::cerr << "Exception thrown while parsing: " << e.what() << '\n'
                  << "Error line: " << e.getLine() << '\n';
        return 1;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception thrown: " << e.what() << '\n';
        return 1;
    }

    return 0;
}