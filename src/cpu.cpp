#include <iostream>
#include "cpu.hpp"


CPUThread::CPUThread(RAM* ram, InstructionParser* parser)
{
	this->ram = ram;
	this->parser = parser;
	this->registers.pc = 0u;
	this->loop();
}


CPURegisters* CPUThread::get_regs(){
	return &(this->registers);
}


void CPUThread::loop(){
	this->running = true;

	while(this->running){
		std::cout << "Starting pc: " << this->registers.pc << std::endl;

		uint32_t instr_raw = this->ram->get(this->registers.pc);
		std::cout << "Raw instruction: " << instr_raw << std::endl;

		AInstruction* instr = this->parser->parse(instr_raw);	

		int32_t pc_offset = instr->execute(this);
		this->registers.pc += pc_offset;

		std::cout << "New pc: " << this->registers.pc << std::endl;

		this->running = false;
	}
}


CPUCore::CPUCore(RAM* ram, InstructionParser* parser):
	thread(CPUThread(ram, parser)){
}

CPU::CPU(RAM* ram) : core(CPUCore(ram, &this->parser)){
}
