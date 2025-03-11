#include "instructions.hpp"
#include "cpu.hpp"

ADD::ADD(uint32_t reg_a, uint32_t reg_b, uint32_t reg_dest){
	this->reg_a = reg_a;
	this->reg_b = reg_b;
	this->reg_dest = reg_dest;
}

int32_t ADD::execute(CPUThread* thread){
	thread->get_regs()->regi[this->reg_dest]
		= thread->get_regs()->regi[this->reg_a]
		  + thread->get_regs()->regi[this->reg_b];

	return 1;
}


ADDI::ADDI(uint32_t reg_a, int32_t imm, uint32_t reg_dest){
	this->reg_a = reg_a;
	this->imm = imm;
	this->reg_dest = reg_dest;
}

int32_t ADDI::execute(CPUThread* thread){
	thread->get_regs()->regi[this->reg_dest]
		= thread->get_regs()->regi[this->reg_a]
		  + this->imm;

	return 1;
}


ISA isa_rv32i(){}


AInstruction* InstructionParser::parse(uint32_t instruction){
	return new ADDI(4, 5, 6);
}
