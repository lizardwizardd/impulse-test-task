#include <iostream>

#include "../inc/computerclub.hpp"
#include "../inc/myexceptions.hpp"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "File name not specified\n";
        return 1;
    }

    try
    {
        ComputerClub computerClub(argv[1]);
        //ComputerClub computerClub("../../sample_input2.txt");
        computerClub.run();
    }
    catch(const ParseException& e)
    {
        std::cerr << "Exception thrown while parsing: " << e.what() << '\n'
                  << "Error line: " << e.getLine() << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
    }

    return 0;
}