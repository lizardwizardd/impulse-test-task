#pragma once

#include <string>
#include <fstream>


// Владет файлом и считывает его по строкам
// Отвечает ровно за один открытый файл все свое время жизни
class FileBuffer
{
private:
    std::string buffer = "";
    size_t bufferSize = 0;
    std::ifstream file;

public:
    FileBuffer() = delete;
    // Открывает файл с именем filename, при неудаче выбрасывает исключение
    FileBuffer(const std::string& filename);
    ~FileBuffer();
    
    // Прочитать и сохранить строку. Возвращает false, если файл закончился
    bool readInputLine();

    // Строка возвращается без пробелов и лишних символов в конце
    std::string getBuffer();
    size_t getSize();
};