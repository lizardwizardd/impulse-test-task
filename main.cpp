#include <iostream>

#include "../inc/computerclub.hpp"

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
        //ComputerClub computerClub("../../sample_input.txt");
        computerClub.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}