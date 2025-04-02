#include "utils.hpp"
#include "instructions.hpp"

#include <cstdint>
#include <iostream>
#include <fstream>
#include <consts.hpp>

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

int32_t sext(uint32_t x, uint32_t pos){
	
	if(bit(x, pos)){
		return x | ((1u << (32 - pos + 1)) - 2) << pos;
	}

	return x;
}

void write_to_stdout(std::string s){
	std::ofstream file;
	file.open(IO_OUT_FILE, std::ios::app);
	file << s;
	file.close();

	std::cout << "[STDOUT]: " << s << std::endl;
}

void clear_stdout(){
	std::ofstream file;
	file.open(IO_OUT_FILE, std::ios::trunc);
	file.close();
}