#include <iostream>
#include "instructions.hpp"
#include "cpu.hpp"

CPURegisters::CPURegisters() : pc(0) { 
	std::fill(std::begin(regi), std::end(regi), 0);
	std::fill(std::begin(regf), std::end(regf), 0.0f);
	this->pc = DEFAULT_START_PC;
	this->regi[2] = DEFAULT_START_SP;
}

void CPURegisters::display(){
	std::cout << "PC: " << this->pc << std::endl;

	for(int i = 0; i < 32; i++){
		std::cout << "IREG" << i << ": " << this->regi[i] << std::endl;
	}

	// for(int i = 0; i < 32; i++){
	// 	std::cout << "FREG" << i << ": " << this->regf[i] << std::endl;
	// }
}

void CPURegisters::set_ri(uint32_t r, int32_t val){
	if (r > 0)
		this->regi[r] = val;
}

int32_t CPURegisters::get_ri(uint32_t r){
	return this->regi[r];
}
CPUThread::CPUThread(RAM* ram, InstructionParser* parser)
{
	this->ram = ram;
	this->parser = parser;
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
		// std::cout << "Loop " << i << std::endl;

		// this->registers.display();

		uint32_t instr_raw = this->ram->get_w(this->registers.pc);
		// std::cout << "Raw instruction: " << instr_raw << std::endl;

		std::unique_ptr<AInstruction> instr = this->parser->parse(instr_raw);	

		std::cout << std::hex;
		std::cout << "[INSTRUCTION (pc=0x" << this->registers.pc << ")] " << instr.get()->to_string() << std::endl;
		std::cout << std::dec;

		int32_t pc_offset = instr->execute(this);
		this->registers.pc += pc_offset;
		// this->registers.display();
		// std::cout << std::endl;

		if(instr_raw == (uint32_t)0) {
			this->running = false;
		}

		i++;
	}

	std::cout << "Final register state: (" << i << " iters)" << std::endl;
	this->registers.display();
}

RAM* CPUThread::get_ram(){
	return this->ram;
}

CPUCore::CPUCore(RAM* ram, InstructionParser* parser):
	thread(CPUThread(ram, parser)){
}

void CPUCore::start(){
	this->thread.start();
}

CPUThread* CPUCore::get_thread(){
	return &this->thread;
}

CPUCore* CPU::get_core(){
	return &this->core;
}

CPU::CPU(RAM* ram, InstructionParser parser) : 
	parser(parser),	
	core(CPUCore(ram, &this->parser))
{}

InstructionParser* CPU::get_parser(){
	return &this->parser;
}
void CPU::start(){
	this->core.start();
}
