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

		RVUnparsedInstr get_rvinstr(uint32_t addr);
		void set_w(uint32_t addr, uint32_t val);
		void set_h(uint32_t addr, uint16_t val);
		void set_b(uint32_t addr, uint8_t  val);
	private:
		uint8_t *mem;
};
