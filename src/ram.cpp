#include "ram.hpp"
#include "rv32i.hpp"
#include "utils.hpp"

RAM::RAM(){
	this->mem = (uint32_t*)malloc(RAM_WORDS * sizeof(uint32_t));
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
