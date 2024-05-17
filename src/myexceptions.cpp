#include "../inc/myexceptions.hpp"

ParseException::ParseException(const std::string& msg, const std::string& line) :
    message(msg),
    line(line)
{}

const char* ParseException::what() const noexcept
{
    return message.c_str();
}

const std::string& ParseException::getLine() const
{
    return line;
}