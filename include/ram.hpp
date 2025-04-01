#pragma once

#include <cstdint>
#include <string>

#include "instructions.hpp"

#define RAM_WORDS 0xFFFFFFFF

class RAM{
	public:
		RAM();
		RAM(std::string load_path);
		~RAM();

		uint32_t get_w(uint32_t addr);
		uint16_t get_h(uint32_t addr);
		uint8_t  get_b(uint32_t addr);

		RVUnparsedInstr get_rvinstr(uint32_t addr){
			RVUnparsedInstrType type;
			RVUnparsedInstrUnion instr;

			uint8_t lower_code = this->mem[addr] & 0x3;
			if(lower_code == 0x1){
				type = RVUnparsedInstrType::INSTR16;
				instr.instr_16 = get_h(addr);
			}else if(lower_code == 0x3){
				type = RVUnparsedInstrType::INSTR32;
				instr.instr_32 = get_w(addr);
			}else{
				type = RVUnparsedInstrType::INSTR64;
				instr.instr_64 = get_w(addr);
			}
			return RVUnparsedInstr(type, instr);
		}
		void set_w(uint32_t addr, uint32_t val);
		void set_h(uint32_t addr, uint16_t val);
		void set_b(uint32_t addr, uint8_t  val);
	private:
		uint8_t *mem;
};
