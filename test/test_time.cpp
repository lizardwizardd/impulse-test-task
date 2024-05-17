#include <gtest/gtest.h>

#include "../inc/mytime.hpp"


TEST(TimeTest, ConstructorString)
{
    Time time("09:30");
    EXPECT_EQ(time.getMins(), 9 * 60 + 30);
}

TEST(TimeTest, ConstructorInt)
{
    Time time(9 * 60 + 30);
    EXPECT_EQ(time.getMins(), 9 * 60 + 30);
}

TEST(TimeTest, SetInvalidStringFormat)
{
    EXPECT_THROW(Time time("9:30"), std::invalid_argument);
    EXPECT_THROW(Time time("1230"), std::invalid_argument);
    EXPECT_THROW(Time time("09-30"), std::invalid_argument);
    EXPECT_THROW(Time time("09:60"), std::invalid_argument);
}

TEST(TimeTest, SetInvalidMinsArgument)
{
    EXPECT_THROW(Time time(24 * 60 + 1), std::invalid_argument);
}

TEST(TimeTest, SetInvalidStringArgument)
{
    EXPECT_THROW(Time time("24:00"), std::invalid_argument);
}

TEST(TimeTest, SetValidString)
{
    Time time;
    time.setTime("09:30");
    EXPECT_EQ(time.getMins(), 9 * 60 + 30);
    time.setTime("00:00");
    EXPECT_EQ(time.getMins(), 0);
}

TEST(TimeTest, SetInvalidMins)
{
    Time time;
    EXPECT_THROW(time.setMins(-1), std::invalid_argument);
    EXPECT_THROW(time.setMins(24 * 60 + 1), std::invalid_argument);
}

TEST(TimeTest, SetValidMins)
{
    Time time;
    time.setMins(9 * 60 + 30);
    EXPECT_EQ(time.getMins(), 9 * 60 + 30);
    time.setMins(0);
    EXPECT_EQ(time.getMins(), 0);
}

TEST(TimeTest, GetFormattedString)
{
    Time time(9 * 60 + 5);
    EXPECT_EQ(time.getFormattedString(), "09:05");

    time.setMins(23 * 60 + 59);
    EXPECT_EQ(time.getFormattedString(), "23:59");

    time.setMins(0);
    EXPECT_EQ(time.getFormattedString(), "00:00");
}

TEST(TimeTest, SubtractOperator)
{
    Time time("01:30");

    Time result = time - Time("01:00");
    EXPECT_EQ(result.getMins(), 30);

    result = time - Time("01:30");
    EXPECT_EQ(result.getMins(), 0);

    result = time - Time("00:00");
    EXPECT_EQ(result.getMins(), 1 * 60 + 30);
}

TEST(TimeTest, SubtractOperatorDayPassed)
{
    Time time("01:30");

    Time result = time - Time("23:59");
    EXPECT_EQ(result.getFormattedString(), "01:31");

    result = time - Time("01:31");
    EXPECT_EQ(result.getFormattedString(), "23:59");

    result = time - Time("02:35");
    EXPECT_EQ(result.getFormattedString(), "22:55");
}
