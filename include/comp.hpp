#pragma once

#include <cstdint>
#include <vector>

#include "cpu.hpp"
#include "ram.hpp"
#include "timer.hpp"
#include "consts.hpp"
#include "compdevices.hpp"



class Comp{
	public:
		Comp(InstructionParser parser);
		Comp(InstructionParser parser, std::string filename);
		void start();

		RAM* get_ram();
		CPU* get_cpu();

	private:
		RAM ram;
		CompDevices devices;
		CPU cpu;
};
