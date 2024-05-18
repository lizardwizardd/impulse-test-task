#pragma once

#include "mytime.hpp"


class Event
{
public:
    enum class Type // TODO 2 enum класса
    {
        UNKNOWN = 0,
        CLIENT_ENTERED = 1,               // клиент зашел
        CLIENT_OCCUPIED_TABLE = 2,        // клиент занял стол
        CLIENT_WAITING = 3,               // клиент ожидает в очереди
        CLIENT_LEFT = 4,                  // клиент ушел

        SUCCESS_NO_EVENT = 10,            // завершено без исходящего события
        CLIENT_LEFT_END_OF_DAY = 11,      // конец дня или полная очередь
        TABLE_FREE_QUEUE_NOT_EMPTY = 12,  // свободный стол при не пустой очереди
        ERROR = 13,                       // ошибка

        ERROR_CLIENT_ALREADY_INSIDE = 101, // клиент уже в очереди
        ERROR_NOT_OPEN_YET = 102,          // клуб еще не открыт
        ERROR_PLACE_IS_BUSY = 103,         // стол занят
        ERROR_CLIENT_UNKNOWN = 104,        // клиент не найден
        ERROR_CLIENT_CAN_NOT_WAIT = 105,   // клиент может не ждать в очереди
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
    // Формат: <время> <тип события> <имя клиента> <номер стола = 0> 
    Type parseLine(const std::string& line);

    // Для тестов
    Type getEventType() const noexcept;
    Time getEventTime() const noexcept;
    std::string getClientName() const noexcept;
    unsigned int getTableNumber() const noexcept;

    void print() const;
};