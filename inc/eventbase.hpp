#pragma once

#include "mytime.hpp"
#include "computerclub.hpp"


class EventBase
{
protected:
    Time eventTime;
    ComputerClub* computerClub = nullptr;

    enum class TypeIn
    {
        UNKNOWN = 0,
        CLIENT_ENTERED = 1,               // клиент зашел
        CLINET_OCCUPIED_TABLE = 2,        // клиент занял стол
        CLIENT_WAITING = 3,               // клиент ожидает в очереди
        CLIENT_LEFT = 4                   // клиент ушел
    };

    enum class TypeOut
    {
        UNKNOWN = 0,
        NO_EVENT = 10,                    // нет исходящего события
        CLIENT_LEFT_END_OF_DAY = 11,      // конец дня
        CLIENT_OCCUPIED_TABLE_QUEUE = 12, // клиент из очереди занял стол
        ERROR = 13                        // ошибка
    };

public:
    EventBase() = default;
    EventBase(ComputerClub* computerClub, Time eventTime) :
        eventTime(eventTime), computerClub(computerClub) {}
    virtual ~EventBase() = default;
};