#pragma once

#include <exception>
#include <string>

class ParseException : public std::exception
{
private:
    std::string message;
    std::string line;

public:
    ParseException(const std::string& msg, const std::string& line);

    const char* what() const noexcept override;
    const std::string& getLine() const;
};