#include <gtest/gtest.h>

#include "../inc/inputbuffer.hpp"


TEST(InputBufferTest, ReadLines)
{
    std::string text = "First line\nSecond line\nThird line\n";
    std::istringstream inputStream(text);

    InputBuffer inputBuffer(inputStream);

    ASSERT_TRUE(inputBuffer.readInputLine());
    EXPECT_EQ(inputBuffer.getBuffer(), "First line");
    EXPECT_EQ(inputBuffer.getSize(), 10);

    ASSERT_TRUE(inputBuffer.readInputLine());
    EXPECT_EQ(inputBuffer.getBuffer(), "Second line");
    EXPECT_EQ(inputBuffer.getSize(), 11);

    ASSERT_TRUE(inputBuffer.readInputLine());
    EXPECT_EQ(inputBuffer.getBuffer(), "Third line");
    EXPECT_EQ(inputBuffer.getSize(), 10);

    ASSERT_FALSE(inputBuffer.readInputLine()); // конец istream
}

TEST(InputBufferTest, ReadEmptyLine)
{
    std::string text = "";
    std::istringstream inputStream(text);

    InputBuffer inputBuffer(inputStream);

    ASSERT_FALSE(inputBuffer.readInputLine());
}

TEST(InputBufferTest, ReadEmptyLinesWithSpaces)
{
    std::string text = " \n      \n";
    std::istringstream inputStream(text);

    InputBuffer inputBuffer(inputStream);

    ASSERT_TRUE(inputBuffer.readInputLine());
    EXPECT_EQ(inputBuffer.getBuffer(), "");
    EXPECT_EQ(inputBuffer.getSize(), 0);

    ASSERT_TRUE(inputBuffer.readInputLine());
    EXPECT_EQ(inputBuffer.getBuffer(), "");
    EXPECT_EQ(inputBuffer.getSize(), 0);

    ASSERT_FALSE(inputBuffer.readInputLine());
}

TEST(InputBufferTest, ReadLinesWithSpaces)
{
    std::string data = "First line    \n Second line \n  \n";
    std::istringstream inputStream(data);

    InputBuffer inputBuffer(inputStream);

    ASSERT_TRUE(inputBuffer.readInputLine());
    EXPECT_EQ(inputBuffer.getBuffer(), "First line");
    EXPECT_EQ(inputBuffer.getSize(), 10);

    ASSERT_TRUE(inputBuffer.readInputLine());
    EXPECT_EQ(inputBuffer.getBuffer(), " Second line");
    EXPECT_EQ(inputBuffer.getSize(), 12);

    ASSERT_TRUE(inputBuffer.readInputLine());
    EXPECT_EQ(inputBuffer.getBuffer(), "");
    EXPECT_EQ(inputBuffer.getSize(), 0);

    ASSERT_FALSE(inputBuffer.readInputLine());
}

TEST(InputBufferTest, ReadInvalidStream)
{
    std::istringstream inputStream("");

    inputStream.setstate(std::ios::failbit);

    EXPECT_THROW(InputBuffer inputBuffer(inputStream), std::runtime_error);
}

TEST(InputBufferTest, SetNewInputStream)
{
    std::string data1 = "Data1 Line 1 \nData1 line 2 \n";
    std::istringstream inputStream1(data1);

    InputBuffer inputBuffer(inputStream1);

    ASSERT_TRUE(inputBuffer.readInputLine());
    EXPECT_EQ(inputBuffer.getBuffer(), "Data1 Line 1");
    EXPECT_EQ(inputBuffer.getSize(), 12);

    std::string data2 = "Data2 other line    \n";
    std::istringstream inputStream2(data2);

    inputBuffer.setInput(inputStream2); // смена потока

    ASSERT_TRUE(inputBuffer.readInputLine());
    EXPECT_EQ(inputBuffer.getBuffer(), "Data2 other line");
    EXPECT_EQ(inputBuffer.getSize(), 16);
}