#include "../inc/inputbuffer.hpp"

InputBuffer::InputBuffer(std::istream& inputStream)
{
    setInput(inputStream);
}

void InputBuffer::setInput(std::istream& inputStream)
{
    if (!inputStream.good())
    {
        throw std::runtime_error("Error: Invalid input stream.");
    }
    input = &inputStream;
}

bool InputBuffer::readInputLine()
{
    if (input == nullptr)
    {
        throw std::runtime_error("Input stream uninitialized.");
    }

    if (!std::getline(*input, buffer))
        return false;

    while (!buffer.empty() && (buffer.back() == ' ' || buffer.back() == '\n' || buffer.back() == '\r'))
        buffer.pop_back();

    bufferSize = buffer.size();
    return true;
}

std::string InputBuffer::getBuffer() noexcept
{
    return buffer;
}

size_t InputBuffer::getSize() noexcept
{
    return bufferSize;
}