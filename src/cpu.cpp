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

void CPURegisters::clear(){
	std::fill(std::begin(regi), std::end(regi), 0);
	std::fill(std::begin(regf), std::end(regf), 0.0f);
	this->pc = 0;
}
void CPURegisters::display(bool newlines) const{
	std::cout << "PC: " << this->pc;

	if (newlines){
		std::cout << std::endl;
	} else {
		std::cout << " | ";
	}
	

	for(int i = 0; i < 32; i++){
		std::cout << "IREG" << i << ": " << this->regi[i];

		if (newlines){
			std::cout << std::endl;
		} else {
			std::cout << " | ";
		}
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
CPUThread::CPUThread(RAM* ram, InstructionParser* parser, CompDevices* devices)
	: parser(parser),
	  ram(ram),
	  devices(devices),
	  running(false),
	  interruptable(true),
	  pre_interrupt_pc(0)
{}


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
		std::cout << "[INSTRUCTION (pc=0x" << this->registers.pc << ")] " << instr.get()->to_string() << " | ";
		this->registers.display(false);
		std::cout << std::endl;

		std::cout << std::dec;

		instr_res = instr->execute(this);
		this->registers.pc += instr_res.pc_offset;
		// this->registers.display();
		// std::cout << std::endl;

		if(instr_raw.instr.instr_32 == 0 || instr_res.flow != ExeFlow::CONTINUE){
			this->running = false;
		}

		for(int i = 0; i < N_TIMERS; i++){
			this->devices->timers[i].tick();
			if(this->devices->timers[i].is_done()){
				std::cout << "[TIMER] Timer " << i << " done" << std::endl;


				uint32_t interrupt_addr = this->devices->timers[i].get_interrupt_addr();
				this->interrupt(interrupt_addr);
				this->devices->timers[i].reset();
			}
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

void CPUThread::interrupt(uint32_t addr){
	if(!this->interruptable){
		//TODO: better things to do here??
		std::cout << "[INTERRUPT] Not interrupting, already interrupted" << std::endl;
		return;
	}
	std::cout << "[INTERRUPT] Interrupting at addr 0x" << std::hex << addr << std::dec << std::endl;
	this->pre_interrupt_pc = this->registers.pc;
	this->registers.pc = addr;
	this->interruptable = false;
}

void CPUThread::uninterrupt(){
	std::cout << "[INTERRUPT] Uninterrupting" << std::endl;
	this->registers.pc = this->pre_interrupt_pc;
	this->interruptable = true;
}

RAM* CPUThread::get_ram(){
	return this->ram;
}

CompDevices* CPUThread::get_devices(){
	return this->devices;
}
CPUCore::CPUCore(RAM* ram, InstructionParser* parser, CompDevices* devices) :
	thread(CPUThread(ram, parser, devices)){
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

CPU::CPU(RAM* ram, InstructionParser parser, CompDevices* devices) : 
	parser(parser),	
	core(CPUCore(ram, &this->parser, devices))
{}

InstructionParser* CPU::get_parser(){
	return &this->parser;
}
void CPU::start(){
	this->core.start();
}
