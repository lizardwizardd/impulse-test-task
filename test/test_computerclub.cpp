#include <gtest/gtest.h>

#include "../inc/computerclub.hpp"
#include "../inc/myexceptions.hpp"

#include <sstream>
#include <string>


TEST(ComputerClubTest, UseCase1) {
    std::stringstream inputString(
        "3\n"
        "09:00 19:00\n"
        "10\n"
        "08:48 1 client1\n"
        "09:41 1 client1\n"
        "09:48 1 client2\n"
        "09:52 3 client1\n"
        "09:54 2 client1 1\n"
        "10:25 2 client2 2\n"
        "10:58 1 client3\n"
        "10:59 2 client3 3\n"
        "11:30 1 client4\n"
        "11:35 2 client4 2\n"
        "11:45 3 client4\n"
        "12:33 4 client1\n"
        "12:43 4 client2\n"
        "15:52 4 client4"
    );

    std::string expectedOutput =
        "09:00\n"
        "08:48 1 client1\n"
        "08:48 13 NotOpenYet\n"
        "09:41 1 client1\n"
        "09:48 1 client2\n"
        "09:52 3 client1\n"
        "09:52 13 ICanWainNoLonger!\n"
        "09:54 2 client1 1\n"
        "10:25 2 client2 2\n"
        "10:58 1 client3\n"
        "10:59 2 client3 3\n"
        "11:30 1 client4\n"
        "11:35 2 client4 2\n"
        "11:35 13 PlaceIsBusy\n"
        "11:45 3 client4\n"
        "12:33 4 client1\n"
        "12:33 12 client4 1\n"
        "12:43 4 client2\n"
        "15:52 4 client4\n"
        "19:00 11 client3\n"
        "19:00\n"
        "1 70 05:58\n"
        "2 30 02:18\n"
        "3 90 08:01\n";

    testing::internal::CaptureStdout();
    ComputerClub computerClub(inputString);
    computerClub.run();
    std::string actualOutput = testing::internal::GetCapturedStdout();

    EXPECT_EQ(expectedOutput, actualOutput);
}

TEST(ComputerClubTest, UseCase2)
{
    std::stringstream inputString(
        "3\n"
        "09:00 19:00\n"
        "10\n"
        "08:48 1 client1\n"
        "09:41 1 client1\n"
        "09:48 1 client2\n"
        "09:52 3 client1\n"
        "09:54 2 client1 1\n"
        "10:25 2 client2 2\n"
        "10:58 1 client3\n"
        "10:59 2 client3 3\n"
        "11:30 1 client4\n"
        "11:35 2 client4 2\n"
        "11:45 3 client4\n"
        "16:00 1 client6\n"
        "16:05 3 client6\n"
        "16:10 1 client7\n"
        "16:15 3 client8\n"
        "17:00 4 client3"
    );

    std::string expectedOutput =
        "09:00\n"
        "08:48 1 client1\n"
        "08:48 13 NotOpenYet\n"
        "09:41 1 client1\n"
        "09:48 1 client2\n"
        "09:52 3 client1\n"
        "09:52 13 ICanWainNoLonger!\n"
        "09:54 2 client1 1\n"
        "10:25 2 client2 2\n"
        "10:58 1 client3\n"
        "10:59 2 client3 3\n"
        "11:30 1 client4\n"
        "11:35 2 client4 2\n"
        "11:35 13 PlaceIsBusy\n"
        "11:45 3 client4\n"
        "16:00 1 client6\n"
        "16:05 3 client6\n"
        "16:10 1 client7\n"
        "16:15 3 client8\n"
        "16:15 13 ClientUnknown\n"
        "17:00 4 client3\n"
        "17:00 12 client4 3\n"
        "19:00 11 client1\n"
        "19:00 11 client2\n"
        "19:00 11 client4\n"
        "19:00 11 client6\n"
        "19:00 11 client7\n"
        "19:00\n"
        "1 100 09:06\n"
        "2 90 08:35\n"
        "3 90 08:01\n";

    testing::internal::CaptureStdout();
    ComputerClub computerClub(inputString);
    computerClub.run();
    std::string actualOutput = testing::internal::GetCapturedStdout();

    EXPECT_EQ(expectedOutput, actualOutput);
}

TEST(ComputerClubTest, UseCase3)
{
    std::stringstream inputString(
        "1\n"
        "22:00 05:00\n"
        "10\n"
        "23:48 1 client1\n"
        "23:41 3 client1\n"
        "23:48 2 client1 1\n"
        "01:00 1 client2\n"
        "01:05 3 client2\n"
        "01:10 2 client2 1\n"
        "02:05 4 client1"
    );

    std::string expectedOutput =
        "22:00\n"
        "23:48 1 client1\n"
        "23:41 3 client1\n"
        "23:41 13 ICanWainNoLonger!\n"
        "23:48 2 client1 1\n"
        "01:00 1 client2\n"
        "01:05 3 client2\n"
        "01:10 2 client2 1\n"
        "01:10 13 PlaceIsBusy\n"
        "02:05 4 client1\n"
        "02:05 12 client2 1\n"
        "05:00 11 client2\n"
        "05:00\n"
        "1 60 05:12\n";

    testing::internal::CaptureStdout();
    ComputerClub computerClub(inputString);
    computerClub.run();
    std::string actualOutput = testing::internal::GetCapturedStdout();

    EXPECT_EQ(expectedOutput, actualOutput);
}

TEST(ComputerClubTest, UseCase4_LeaveFromQueue)
{
    std::stringstream inputString(
        "1\n"
        "09:00 19:00\n"
        "10\n"
        "11:00 1 client1\n"
        "11:05 2 client1 1\n"
        "12:00 1 client2\n"
        "12:05 3 client2\n"
        "12:20 1 client3\n"
        "12:25 3 client3 1\n"
        "13:10 4 client2\n"
        "13:55 4 client1\n"
    );

    std::string expectedOutput =
        "09:00\n"
        "11:00 1 client1\n"
        "11:05 2 client1 1\n"
        "12:00 1 client2\n"
        "12:05 3 client2\n"
        "12:20 1 client3\n"
        "12:25 3 client3 1\n"
        "13:10 4 client2\n"
        "13:55 4 client1\n"
        "13:55 12 client3 1\n"
        "19:00 11 client3\n"
        "19:00\n"
        "1 90 07:55\n";

    testing::internal::CaptureStdout();
    ComputerClub computerClub(inputString);
    computerClub.run();
    std::string actualOutput = testing::internal::GetCapturedStdout();

    EXPECT_EQ(expectedOutput, actualOutput);
}