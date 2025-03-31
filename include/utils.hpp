#pragma once

#include <cstdint>
#include <iostream>

// Gets the lower'th to the upper'th bits in x, inclusive on both sides
// No error checking, so we assum:
// 1. lower >= 0
// 2. upper < 32
// 3. upper >= lower
uint32_t bits(uint32_t x, uint32_t lower, uint32_t upper);

uint32_t bit(uint32_t val, uint32_t pos);

uint32_t set_bits(
    uint32_t target, 
    uint32_t lower, 
    uint32_t upper, 
    uint32_t val);

int32_t sext(uint32_t x, uint32_t pos);

//FIXME: Can probably take something more efficient than a std::string
//FIXME: I imagine this could probably be stored somewhere smarter, especially
//	when fleshed out a bit. For now, it can just live in utils.
void write_to_stdout(std::string s);
