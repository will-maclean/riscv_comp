#include "ram.hpp"
#include "rv32i.hpp"
#include "utils.hpp"

#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>

RAM::RAM(){
	this->mem = (uint8_t*)malloc(RAM_WORDS * sizeof(uint32_t));
}

RAM::RAM(std::string load_path){
	this->mem = (uint8_t*)malloc(RAM_WORDS * sizeof(uint32_t));

	std::ifstream file( load_path, std::ios::binary | std::ios::ate);

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(this->mem), size);
    file.close();
}

RAM::~RAM(){
	free(this->mem);
}

uint32_t RAM::get_w(uint32_t addr){
	uint32_t res = 0;
	res = set_bits(res,  0,  7, this->mem[addr+0]);
	res = set_bits(res,  8, 15, this->mem[addr+1]);
	res = set_bits(res, 16, 23, this->mem[addr+2]);
	res = set_bits(res, 24, 31, this->mem[addr+3]);
	return res;
}

uint16_t RAM::get_h(uint32_t addr){
	uint16_t res = 0;
	res = set_bits(res,  0,  7, this->mem[addr+0]);
	res = set_bits(res,  8, 15, this->mem[addr+1]);
	return res;
}
uint8_t RAM::get_b(uint32_t addr){
	return this->mem[addr];
}
void RAM::set_w(uint32_t addr, uint32_t val){
	if(addr == 0xFFFFFFFF){
		std::cout << val;
	}
	this->mem[addr+0] = bits(val,  0,  7);
	this->mem[addr+1] = bits(val,  8, 15);
	this->mem[addr+2] = bits(val, 16, 23);
	this->mem[addr+3] = bits(val, 24, 31);
}

void RAM::set_h(uint32_t addr, uint16_t val){
	this->mem[addr+0] = bits(val,  0,  7);
	this->mem[addr+1] = bits(val,  8, 15);
}
void RAM::set_b(uint32_t addr, uint8_t val){
	this->mem[addr+0] = val;
}
