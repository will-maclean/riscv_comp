#include "ram.hpp"
#include <utils.hpp>

RAM::RAM(){
	this->mem = (uint32_t*)malloc(RAM_WORDS * sizeof(uint32_t));

	// manually load a few instructions in for fun
	uint32_t new_instr = 0;
	new_instr = set_bits(new_instr,  0,  6, 0b0010011);			// opcode
	new_instr = set_bits(new_instr, 12, 14, 0b000); 			// funct3
	new_instr = set_bits(new_instr, 15, 19, 0b00000); 			// src
	new_instr = set_bits(new_instr,  7, 11, 0b00001); 			// dest
	new_instr = set_bits(new_instr, 20, 31, 0b111111111111);	// imm

	this->mem[0] = new_instr;
}

RAM::RAM(std::string load_path){
}

RAM::~RAM(){
	free(this->mem);
}

uint32_t RAM::get(uint32_t addr){
	return this->mem[addr];
}

void RAM::set(uint32_t addr, uint32_t val) {
	this->mem[addr] = val;
}
