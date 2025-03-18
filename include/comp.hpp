#pragma once

#include <cstdint>
#include <vector>

#include "cpu.hpp"
#include "ram.hpp"


class Comp{
	public:
		Comp(InstructionParser parser);

	private:
		RAM ram;
		CPU cpu;
};
