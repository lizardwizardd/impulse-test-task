#pragma once

#include <string>
#include <fstream>


// Отвечает за управление файлом и считывает его по строкам
class FileBuffer
{
private:
    std::string buffer = "";
    size_t bufferSize = 0;
    std::ifstream file;

public:
    FileBuffer() = delete;
    FileBuffer(const std::string& filename);
    ~FileBuffer();

    // Прочитать и сохранить строку. Возвращает false, если файл закончился
    bool readInputLine();

    // Получить строку без пробелов и лишних символов
    std::string getBuffer();
    size_t getSize();
};