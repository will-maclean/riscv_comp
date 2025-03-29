#include "ram.hpp"
#include "rv32i.hpp"
#include "utils.hpp"

#include <fstream>
#include <iterator>
#include <algorithm>

RAM::RAM(){
	this->mem = (uint32_t*)malloc(RAM_WORDS * sizeof(uint32_t));

	this->mem[0] = ADDI(0, 42, 1).to_instruction();
	this->mem[1] = ADDI(0, -10, 2).to_instruction();
	this->mem[2] = ADD(1, 2, 3).to_instruction();
}

RAM::RAM(std::string load_path){
	this->mem = (uint32_t*)malloc(RAM_WORDS * sizeof(uint32_t));

	std::ifstream file( load_path, std::ios::binary );

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint32_t> data(size / 4);
    file.read(reinterpret_cast<char*>(data.data()), size);
    file.close();

    for (uint32_t value : data) {
        std::cout << "0x" << std::hex << value << std::dec << std::endl;
    }
	for(int i = 0; i < data.size(); i++){
		this->mem[i] = data.at(i);
	}
}

RAM::~RAM(){
	free(this->mem);
}

uint32_t RAM::get(uint32_t addr){
	return this->mem[addr];
}

void RAM::set(uint32_t addr, uint32_t val) {
	if(addr == 1234){
		std::cout << val;
	}
	this->mem[addr] = val;
}
