#include <gtest/gtest.h>
#include "instructions.hpp"


TEST(UTILSTest, ExtractImmI){
	// 12 imm bits, in 20-31
	// lets load them with 0b111111111111
	// = 4095 unsigned, or -1 signed
	uint32_t instr = 0b11111111111100000000000000000000;

	int32_t signed_res = extract_imm_signed32(instr, ImmType::I);
	uint32_t unsigned_res = extract_imm_unsigned32(instr, ImmType::I);

    EXPECT_EQ(signed_res, -1);
    EXPECT_EQ(unsigned_res, 4095);

}
TEST(UTILSTest, ExtractImmJ){
	uint32_t instr = 0x03c0006f;

	int32_t signed_res = extract_imm_signed32(instr, ImmType::J);

    EXPECT_EQ(signed_res, 60);
}