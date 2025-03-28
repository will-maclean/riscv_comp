#include <gtest/gtest.h>
#include "utils.hpp"

TEST(UTILSTest, GetBits) {
	// multi-bits
	uint32_t x = 0b1100;
	uint32_t res = 0b11;
	
	EXPECT_EQ(bits(x, 2, 3), res);

	// single bit
	res = 0b1;
	EXPECT_EQ(bits(x, 2, 2), res);	

	// test nothing weird happens if it's zeros instead of ones
	x = 0b100111;
	res = 0b0;
	EXPECT_EQ(bits(x, 3, 4), res);
}

TEST(UTILSTest, GetBit) {
	uint32_t x = 0b0011;

	uint32_t res = 0;
	EXPECT_EQ(bit(x,2), res);

	res = 1;
	EXPECT_EQ(bit(x,1), res);
}

TEST(UTILSTest, SetBits) {
	uint32_t x = 0b001100;
	uint32_t set = 0b00;

	// this one shouldn't change anything
	EXPECT_EQ(set_bits(x, 0, 1, set), x);

	// this one should wipe the whole thing out
	uint32_t res = 0;
	EXPECT_EQ(set_bits(x, 2, 3, set), res);

	// this one should set some vals
	set = 0b11;
	res = 0b111100;
	EXPECT_EQ(set_bits(x, 4, 5, set), res);
}


TEST(UTILSTest, SEXT){
	ASSERT_EQ(sext(1u, 1), 1);
	ASSERT_EQ(sext(3u, 1), -1);
}