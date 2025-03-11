#pragma once

#include <cstdint>
#include <string>

#define RAM_WORDS 0xFFFFFFFF

class RAM{
	public:
		RAM();
		RAM(std::string load_path);
		~RAM();

		uint32_t get(uint32_t addr);
		void set (uint32_t addr, uint32_t val);
	private:
		uint32_t *mem;
};
