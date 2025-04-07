#include "ram.hpp"
#include "rv32i.hpp"
#include "utils.hpp"
#include "consts.hpp"

#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <sstream>

template<typename T>
void write_to_rom_warning(uint32_t addr, T val){
	std::cout << "[WARNING] Attempt to write to ROM at addr=0x" << std::hex << addr << ", val=0x" << std::hex << val << std::endl;
}

RAM::RAM(): protecting_rom(false), rom_last_addr(0){
	this->mem = (uint8_t*)malloc(RAM_WORDS * sizeof(uint32_t));
}

RAM::RAM(std::string load_path): protecting_rom(ROM_PROTECT_BINARY){
	this->mem = (uint8_t*)malloc(RAM_WORDS * sizeof(uint32_t));

	std::ifstream file( load_path, std::ios::binary | std::ios::ate);

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
	this->rom_last_addr = size;
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
	if(this->protecting_rom && addr < this->rom_last_addr){
		write_to_rom_warning(addr, val);
		return;
	}
	this->mem[addr+0] = bits(val,  0,  7);
	this->mem[addr+1] = bits(val,  8, 15);
	this->mem[addr+2] = bits(val, 16, 23);
	this->mem[addr+3] = bits(val, 24, 31);
}

void RAM::set_h(uint32_t addr, uint16_t val){
	if(this->protecting_rom && addr < this->rom_last_addr){
		write_to_rom_warning(addr, val);
		return;
	}
	this->mem[addr+0] = bits(val,  0,  7);
	this->mem[addr+1] = bits(val,  8, 15);
}
void RAM::set_b(uint32_t addr, uint8_t val){
	if(this->protecting_rom && addr < this->rom_last_addr){
		write_to_rom_warning(addr, val);
		return;
	}
	this->mem[addr+0] = val;
}

RVUnparsedInstr RAM::get_rvinstr(uint32_t addr){
	RVUnparsedInstrType type;
	RVUnparsedInstrUnion instr;

	uint8_t lower_code = this->mem[addr] & 0x3;
	if(lower_code == 0x3){
		type = RVUnparsedInstrType::INSTR32;
		instr.instr_32 = get_w(addr);
	}else {
		type = RVUnparsedInstrType::INSTR16;
		instr.instr_16 = get_h(addr);
	}
	return RVUnparsedInstr(type, instr);
}