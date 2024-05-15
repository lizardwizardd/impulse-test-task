#include "../inc/filebuffer.hpp"

FileBuffer::FileBuffer(const std::string& filename) : file(filename)
{
    if (!file.is_open())
    {
        throw std::runtime_error("Error opening file '" + filename + "'. \n" +
            "Make sure the input file is in the same directory as the executable or specify a relative path.");
    }
}

FileBuffer::~FileBuffer()
{
    file.close();
}

bool FileBuffer::readInputLine()
{
    if (!std::getline(file, buffer))
        return false;

    while (!buffer.empty() && (buffer.back() == ' ' || buffer.back() == '\n' || buffer.back() == '\r'))
        buffer.pop_back();

    bufferSize = buffer.size();
    return true;
}

std::string FileBuffer::getBuffer()
{
    return buffer;
}

size_t FileBuffer::getSize()
{
    return bufferSize;
}

