#pragma once

#include <string>
#include <istream>


// Считывает полученный поток по строкам, не владеет им
class InputBuffer
{
private:
    std::string buffer = "";
    size_t bufferSize = 0;
    std::istream* input = nullptr;

public:
    InputBuffer() = default;
    // Открывает поток, при неудаче выбрасывает исключение
    InputBuffer(std::istream& inputStream);
    ~InputBuffer() = default;

    // input не изменяется в случае ошибки
    void setInput(std::istream& inputStream);

    // Прочитать и сохранить строку. Возвращает false, если поток закончился
    bool readInputLine();

    // Возвращает строку без пробелов и лишних символов в конце
    std::string getBuffer() noexcept;
    size_t getSize() noexcept;
};
