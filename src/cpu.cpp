#include <iostream>
#include "instructions.hpp"
#include "cpu.hpp"
#include "consts.hpp"

CPURegisters::CPURegisters() { 
	std::fill(std::begin(regi), std::end(regi), 0);
	std::fill(std::begin(regf), std::end(regf), 0.0f);
	this->pc = DEFAULT_START_PC;
	this->regi[2] = DEFAULT_START_SP;
}

void CPURegisters::display() const{
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

int32_t CPURegisters::get_ri(uint32_t r) const{
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
	InstrResult instr_res(0, ExeFlow::CONTINUE);
	while(this->running){
		// std::cout << "Loop " << i << std::endl;

		// this->registers.display();

		RVUnparsedInstr instr_raw = this->ram->get_rvinstr(this->registers.pc);
		// std::cout << "Raw instruction: " << instr_raw << std::endl;

		std::unique_ptr<AInstruction> instr = this->parser->parse(instr_raw);	

		std::cout << std::hex;
		std::cout << "[INSTRUCTION (pc=0x" << this->registers.pc << ")] " << instr.get()->to_string() << std::endl;
		std::cout << std::dec;

		instr_res = instr->execute(this);
		this->registers.pc += instr_res.pc_offset;
		// this->registers.display();
		// std::cout << std::endl;

		if(instr_raw.instr.instr_32 == 0 || instr_res.flow != ExeFlow::CONTINUE){
			this->running = false;
		}

		i++;
	}

	if(instr_res.flow == ExeFlow::ERROR){
		std::cout << "Thread ended unsuccessfully" << std::endl;
		std::cout << "Final register state: (" << i << " iters)" << std::endl;
		this->registers.display();
	} else {
		std::cout << "Thread ended successfully" << std::endl;
	}
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
