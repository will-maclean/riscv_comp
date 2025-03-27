#pragma once

#include "ram.hpp"
#include "instructions.hpp"


const uint32_t DEFAULT_START_PC = 0x0;


// Has both int and float registers
struct CPURegisters{
	uint32_t pc;
	int32_t regi[32];

	//FIXME: force this to be a 32-bit floating point register
	float regf[32];

	CPURegisters();
	void display();
};


class CPUThread{
	public:
		// Just a stub - at some point we'll need to pass in a 
		// instruction pointer
		CPUThread(RAM* ram, InstructionParser* parser);
		void start();

		CPURegisters* get_regs();
		RAM* get_ram();

	private:
		void loop();

		InstructionParser* parser;
		RAM* ram;
		CPURegisters registers;

		bool running;
};

class CPUCore{
	public:
		CPUCore(RAM* ram, InstructionParser* parser);
		void start();
	private:
		// just one thread for now, can support multi-threading later
		CPUThread thread;
};

class CPU{
	public:
		CPU(RAM* ram, InstructionParser parser);
		void start();
	private:
		//just one thread for now, can support multi-core later
		CPUCore core;

		InstructionParser parser;
};
