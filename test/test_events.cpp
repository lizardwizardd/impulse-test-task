#include <gtest/gtest.h>

#include "../inc/eventbase.hpp"
#include "../inc/eventin.hpp"
#include "../inc/eventout.hpp"

#include <../inc/computerclub.hpp>

TEST(EventBaseTest, Constructor)
{
    ComputerClub* computerClub = nullptr;
    EXPECT_NO_THROW(EventBase(computerClub, Time("12:00")));
}