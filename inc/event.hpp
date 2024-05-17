#pragma once

#include "mytime.hpp"


class Event
{
public:
    enum class Type
    {
        UNKNOWN = 0,
        CLIENT_ENTERED = 1,               // клиент зашел
        CLINET_OCCUPIED_TABLE = 2,        // клиент занял стол
        CLIENT_WAITING = 3,               // клиент ожидает в очереди
        CLIENT_LEFT = 4,                  // клиент ушел

        NO_EVENT = 10,                    // нет исходящего события
        CLIENT_LEFT_END_OF_DAY = 11,      // конец дня
        CLIENT_OCCUPIED_TABLE_QUEUE = 12, // клиент из очереди занял стол
        ERROR = 13                        // ошибка
    };

private:
    Time eventTime;
    Type eventType = Type::UNKNOWN;
    std::string clientName = "";
    unsigned int tableNumber = 0;

public:
    Event() = default;
    Event(Time eventTime, Type eventType = Type::UNKNOWN,
          std::string clientName = "", unsigned int tableNumber = 0);

    // Считывает строку и возвращает тип события
    Type parseLine(const std::string& line);
    Type getEventType() const noexcept;
    Time getEventTime() const noexcept;
    void print() const;
};