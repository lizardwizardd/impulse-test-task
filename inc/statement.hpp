#pragma once

#include <string>
#include <iostream>


enum class Event
{
    UNKNOWN,
    CLIENT_ENTERED,                   // клиент зашел
    CLINET_OCCUPIED_TABLE,            // клиент занял стол
    CLIENT_WAITING,                   // клиент ожидает в очереди
    CLIENT_LEFT,                      // клиент ушел

    CLIENT_LEFT_END_OF_DAY = 11,      // конец дня
    CLIENT_OCCUPIED_TABLE_QUEUE = 12, // клиент из очереди занял стол
    ERROR = 13                        // ошибка
};

class Statement
{

};