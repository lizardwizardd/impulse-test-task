#include <gtest/gtest.h>

#include "../inc/mytime.hpp"
#include "../inc/event.hpp"
#include "../inc/computerclub.hpp"
#include "../inc/myexceptions.hpp"


TEST(EventTest, Constructor)
{
    Event event(Time("18:30"), Event::Type::CLIENT_WAITING, "client1", 1);

    EXPECT_EQ(event.getEventTime(), Time(18 * 60 + 30));
    EXPECT_EQ(event.getEventType(), Event::Type::CLIENT_WAITING);
    EXPECT_EQ(event.getClientName(), "client1");
    EXPECT_EQ(event.getTableNumber(), 1);
}

TEST(EventTest, ParseThreeArguments)
{
    Event event;
    Event::Type type = event.parseLine("12:30 4 client3");

    EXPECT_EQ(type, Event::Type::CLIENT_LEFT);
    EXPECT_EQ(event.getEventTime(), Time("12:30"));
    EXPECT_EQ(event.getEventType(), Event::Type::CLIENT_LEFT);
    EXPECT_EQ(event.getClientName(), "client3");
    EXPECT_EQ(event.getTableNumber(), 0);
}

TEST(EventTest, ParseLineWithFourArguments)
{
    Event event;
    Event::Type type = event.parseLine("08:05 2 client1 4");

    EXPECT_EQ(type, Event::Type::CLIENT_OCCUPIED_TABLE);
    EXPECT_EQ(event.getEventTime(), Time("08:05"));
    EXPECT_EQ(event.getEventType(), Event::Type::CLIENT_OCCUPIED_TABLE);
    EXPECT_EQ(event.getClientName(), "client1");
    EXPECT_EQ(event.getTableNumber(), 4);
}

TEST(EventTest, ParseLineWithTooManySpaces)
{
    Event event;
    Event::Type type = event.parseLine("08:05   2   client1   4");

    EXPECT_EQ(type, Event::Type::CLIENT_OCCUPIED_TABLE);
    EXPECT_EQ(event.getEventTime(), Time("08:05"));
    EXPECT_EQ(event.getEventType(), Event::Type::CLIENT_OCCUPIED_TABLE);
    EXPECT_EQ(event.getClientName(), "client1");
    EXPECT_EQ(event.getTableNumber(), 4);
}

TEST(EventTest, ParseInvalidFormatTime)
{
    Event event;
    EXPECT_THROW(event.parseLine("8:05 2 client1"), ParseException);
}

TEST(EventTest, ParseTooFewArgs)
{
    Event event;
    EXPECT_THROW(event.parseLine("22:30 2"), ParseException);
}

/*
TEST(EventTest, ParseTooManyArgs)
{
    Event event;
    EXPECT_THROW(event.parseLine("22:30 2 client1 4 5"), ParseException);
}
*/

TEST(EventTest, ParseWrongType)
{
    Event event;
    EXPECT_THROW(event.parseLine("08:05 type1 client1"), ParseException);
}

TEST(EventTest, PrintThreeArguments)
{
    Event event(Time("18:30"), Event::Type::CLIENT_LEFT, "client1", 0);

    testing::internal::CaptureStdout();
    event.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "18:30 4 client1\n");
}

TEST(EventTest, PrintFourArguments)
{
    Event event(Time("18:30"), Event::Type::CLIENT_OCCUPIED_TABLE, "client1", 4);

    testing::internal::CaptureStdout();
    event.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "18:30 2 client1 4\n");
}
