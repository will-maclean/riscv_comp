#include <gtest/gtest.h>
#include "ram.hpp"

TEST(RAMTest, ReadWrite) {
    RAM ram;
    ram.set_w(0, 42);
    EXPECT_EQ(ram.get_w(0), 42);
}
