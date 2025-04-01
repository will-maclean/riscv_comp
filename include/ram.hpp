#pragma once

#include <cstdint>
#include <string>

#include "instructions.hpp"

constexpr uint32_t RAM_WORDS = 0xFFFFFFFF;
constexpr bool ROM_PROTECT_BINARY = true;

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
		bool protecting_rom = false;
		uint32_t rom_last_addr;
};
