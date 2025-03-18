#include <gtest/gtest.h>
#include "ram.hpp"  // Include the header file for RAM (or other components)

TEST(RAMTest, ReadWrite) {
    RAM ram;
    ram.set(0, 42);  // Write value to RAM at address 0
    EXPECT_EQ(ram.get(0), 42);  // Verify the value read from RAM is 42
}
