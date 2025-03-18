#pragma once

#include <cstdint>

// Gets the lower'th to the upper'th bits in x, inclusive on both sides
// No error checking, so we assum:
// 1. lower >= 0
// 2. upper < 32
// 3. upper >= lower
inline uint32_t bits(uint32_t x, uint32_t lower, uint32_t upper) {
	return (x >> lower) & (1 << (upper - lower) - 1);
}

inline uint32_t bit(uint32_t val, uint32_t pos){
    return val & (1 << pos) == 1;
}

inline uint32_t set_bits(
    uint32_t target, 
    uint32_t lower, 
    uint32_t upper, 
    uint32_t val){
    
    return target & (
        bits(val, lower, upper) << (upper - lower)
    );
}