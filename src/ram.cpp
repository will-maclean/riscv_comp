#include "ram.hpp"
#include "rv32i.hpp"
#include "utils.hpp"

RAM::RAM(){
	this->mem = (uint32_t*)malloc(RAM_WORDS * sizeof(uint32_t));

	this->mem[0] = ADDI(0, 42, 1).to_instruction();
	this->mem[1] = ADDI(0, -10, 2).to_instruction();
	this->mem[2] = ADD(1, 2, 3).to_instruction();
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
