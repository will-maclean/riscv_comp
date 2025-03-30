#pragma once

#include "ram.hpp"
#include "instructions.hpp"


const uint32_t DEFAULT_START_PC = 0x1000;
const uint32_t DEFAULT_START_SP = 0xFFFFFFE;


// Has both int and float registers
class CPURegisters{
public:
	CPURegisters();
	void display();
	void set_ri(uint32_t r, int32_t val);
	int32_t get_ri(uint32_t r);
	uint32_t pc;
private:
	int32_t regi[32];

	//FIXME: force this to be a 32-bit floating point register
	float regf[32];
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

		CPUThread* get_thread();
	private:
		// just one thread for now, can support multi-threading later
		CPUThread thread;
};

class CPU{
	public:
		CPU(RAM* ram, InstructionParser parser);
		void start();

		CPUCore* get_core();
		InstructionParser* get_parser();
	private:
		InstructionParser parser;
		//just one thread for now, can support multi-core later
		CPUCore core;

};
