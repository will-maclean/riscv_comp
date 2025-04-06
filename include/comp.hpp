#pragma once

#include <cstdint>
#include <vector>

#include "cpu.hpp"
#include "ram.hpp"


class Comp{
	public:
		Comp(InstructionParser parser);
		Comp(InstructionParser parser, std::string filename);
		void start();

		RAM* get_ram();
		CPU* get_cpu();

	private:
		RAM ram;
		CPU cpu;
};
