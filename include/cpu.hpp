#pragma once

#include "ram.hpp"
#include "instructions.hpp"
#include "compdevices.hpp"


// Has both int and float registers
class CPURegisters{
public:
	CPURegisters();
	void display() const{display(true);};
	void display(bool newlines) const;
	void clear();
	void set_ri(uint32_t r, int32_t val);
	int32_t get_ri(uint32_t r) const;
	uint32_t pc;
private:
	int32_t regi[32];

	//FIXME: force this to be a 32-bit floating point register
	float regf[32];
};


class CPUThread{
	public:
		CPUThread(RAM* ram, InstructionParser* parser, CompDevices* devices);
		void start();

		// Marked as virtual so we can mock them
		virtual CPURegisters* get_regs();
		virtual RAM* get_ram();
		virtual CompDevices* get_devices();

	private:
		void loop();
		void interrupt(uint32_t addr);

		InstructionParser* parser;
		RAM* ram;
		CompDevices* devices;
		CPURegisters registers;

		bool running;
};

class CPUCore{
	public:
		CPUCore(RAM* ram, InstructionParser* parser, CompDevices* devices);
		void start();

		CPUThread* get_thread();
	private:
		// just one thread for now, can support multi-threading later
		CPUThread thread;
};

class CPU{
	public:
		CPU(RAM* ram, InstructionParser parser, CompDevices* devices);
		void start();

		CPUCore* get_core();
		InstructionParser* get_parser();
	private:
		InstructionParser parser;
		//just one thread for now, can support multi-core later
		CPUCore core;

};
