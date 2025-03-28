#include "utils.hpp"
#include "instructions.hpp"

#include <cstdint>
#include <iostream>

// Gets the lower'th to the upper'th bits in x, inclusive on both sides
// No error checking, so we assum:
// 1. lower >= 0
// 2. upper < 32
// 3. upper >= lower
uint32_t bits(uint32_t x, uint32_t lower, uint32_t upper) {
	return (x >> lower) & ((1 << (upper - lower + 1)) - 1);
}

uint32_t bit(uint32_t val, uint32_t pos){
    return (val >> pos) & 1;
}

uint32_t set_bits(
    uint32_t target, 
    uint32_t lower, 
    uint32_t upper, 
    uint32_t val){

	// 1. Save the unaffected bits
	// (holy bit-level yuckiness)
	uint32_t untouched = target & ~(((1 << (upper - lower + 1)) - 1) << lower);
	
	// 2. Build insert mask
	uint32_t insert = bits(val, 0, upper - lower) << lower;

	// 3. Insert
	return untouched | insert;	
}

int32_t imm_to_signed(uint32_t x){
	int32_t res = (int32_t)bits(x, 0, 30);

	if(bit(res, 31) != POSITIVE_BIT){
		res *= -1;
	}

	return res;
}

int32_t sext(uint32_t x, uint32_t pos){
	
	if(bit(x, pos)){
		return x | ((1u << (32 - pos + 1)) - 2) << pos;
	}

	return x;
}
