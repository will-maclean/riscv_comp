#include <iostream>
#include "instructions.hpp"
#include "cpu.hpp"

CPURegisters::CPURegisters() : pc(0) { 
	std::fill(std::begin(regi), std::end(regi), 0);
	std::fill(std::begin(regf), std::end(regf), 0.0f);
}

void CPURegisters::display(){
	std::cout << "PC: " << this->pc << std::endl;

	for(int i = 0; i < 32; i++){
		std::cout << "IREG" << i << ": " << this->regi[i] << std::endl;
	}

	for(int i = 0; i < 32; i++){
		std::cout << "FREG" << i << ": " << this->regf[i] << std::endl;
	}
}

CPUThread::CPUThread(RAM* ram, InstructionParser* parser)
{
	this->ram = ram;
	this->parser = parser;
	this->registers.pc = 0u;
}


CPURegisters* CPUThread::get_regs(){
	return &(this->registers);
}

void CPUThread::start(){
	this->loop();
}

void CPUThread::loop(){
	this->running = true;

	int i = 0;
	while(this->running){
		std::cout << "Loop " << i << std::endl;

		this->registers.display();

		uint32_t instr_raw = this->ram->get(this->registers.pc);
		std::cout << "Raw instruction: " << instr_raw << std::endl;

		std::unique_ptr<AInstruction> instr = this->parser->parse(instr_raw);	

		int32_t pc_offset = instr->execute(this);
		this->registers.pc += pc_offset;

		std::cout << std::endl;

		if(instr_raw == (uint32_t)0) {
			this->running = false;
		}

		i++;
	}

	std::cout << "Final register state:" << std::endl;
	this->registers.display();
}


CPUCore::CPUCore(RAM* ram, InstructionParser* parser):
	thread(CPUThread(ram, parser)){
}

void CPUCore::start(){
	this->thread.start();
}
CPU::CPU(RAM* ram, InstructionParser parser) : 
	parser(parser),	
	core(CPUCore(ram, &parser))
{}

void CPU::start(){
	this->core.start();
}
