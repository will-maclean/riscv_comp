#include "instructions.hpp"
#include "cpu.hpp"
#include "utils.hpp"

#include <iostream>
#include <memory>

UndefInstr::UndefInstr(uint32_t instr):instr(instr){}

int32_t UndefInstr::execute(CPUThread* thread){
	std::cout << "Unknown instruction: " << this->instr << std::endl;

	return 1u;
}

ADD::ADD(uint32_t reg_a, uint32_t reg_b, uint32_t reg_dest)
	:reg_a(reg_a),
	reg_b(reg_b),
	reg_dest(reg_dest)
{}

int32_t ADD::execute(CPUThread* thread){
	thread->get_regs()->regi[this->reg_dest]
		= thread->get_regs()->regi[this->reg_a]
		  + thread->get_regs()->regi[this->reg_b];

	return 1;
}


ADDI::ADDI(uint32_t reg_a, int32_t imm, uint32_t reg_dest)
	:reg_a(reg_a),
	imm(imm),
	reg_dest(reg_dest)
{}

int32_t ADDI::execute(CPUThread* thread){
	thread->get_regs()->regi[this->reg_dest]
		= thread->get_regs()->regi[this->reg_a]
		  + this->imm;

	return 1;
}

SLLI::SLLI(uint32_t reg_a, int32_t imm, uint32_t reg_dest)
	:reg_a(reg_a),
	imm(imm),
	reg_dest(reg_dest)
{}

int32_t SLLI::execute(CPUThread* thread){
	thread->get_regs()->regi[this->reg_dest]
		= thread->get_regs()->regi[this->reg_a]
		  << this->imm;

	return 1;
}

SLTI::SLTI(uint32_t reg_a, int32_t imm, uint32_t reg_dest)
	:reg_a(reg_a),
	imm(imm),
	reg_dest(reg_dest)
{}

int32_t SLTI::execute(CPUThread* thread){
	
	if((int32_t)this->reg_a < )

	return 1;
}

SLTIU::SLTIU(uint32_t reg_a, int32_t imm, uint32_t reg_dest)
	:reg_a(reg_a),
	imm(imm),
	reg_dest(reg_dest)
{}

int32_t SLTIU::execute(CPUThread* thread){
	thread->get_regs()->regi[this->reg_dest]
		= thread->get_regs()->regi[this->reg_a]
		  + this->imm;

	return 1;
}

XORI::XORI(uint32_t reg_a, int32_t imm, uint32_t reg_dest)
	:reg_a(reg_a),
	imm(imm),
	reg_dest(reg_dest)
{}

int32_t XORI::execute(CPUThread* thread){
	thread->get_regs()->regi[this->reg_dest]
		= thread->get_regs()->regi[this->reg_a]
		  + this->imm;

	return 1;
}

ANDI::ANDI(uint32_t reg_a, int32_t imm, uint32_t reg_dest)
	:reg_a(reg_a),
	imm(imm),
	reg_dest(reg_dest)
{}

int32_t ANDI::execute(CPUThread* thread){
	thread->get_regs()->regi[this->reg_dest]
		= thread->get_regs()->regi[this->reg_a]
		  + this->imm;

	return 1;
}

SRLI::SRLI(uint32_t reg_a, int32_t imm, uint32_t reg_dest)
	:reg_a(reg_a),
	imm(imm),
	reg_dest(reg_dest)
{}

int32_t SRLI::execute(CPUThread* thread){
	thread->get_regs()->regi[this->reg_dest]
		= thread->get_regs()->regi[this->reg_a]
		  + this->imm;

	return 1;
}

SRAI::SRAI(uint32_t reg_a, int32_t imm, uint32_t reg_dest)
	:reg_a(reg_a),
	imm(imm),
	reg_dest(reg_dest)
{}

int32_t SRAI::execute(CPUThread* thread){
	thread->get_regs()->regi[this->reg_dest]
		= thread->get_regs()->regi[this->reg_a]
		  + this->imm;

	return 1;
}

ORI::ORI(uint32_t reg_a, int32_t imm, uint32_t reg_dest)
	:reg_a(reg_a),
	imm(imm),
	reg_dest(reg_dest)
{}

int32_t ORI::execute(CPUThread* thread){
	thread->get_regs()->regi[this->reg_dest]
		= thread->get_regs()->regi[this->reg_a]
		  + this->imm;

	return 1;
}

std::unique_ptr<AInstruction> op_imm(uint32_t instr){
	// by definition, but we can say it here explicitly as well
	uint32_t opcode = 0b0010011;
	uint32_t rd = bits(instr, 7, 11);
	uint32_t funct3 = bits(instr, 12, 14);
	uint32_t rs1 = bits(instr, 15, 19);
	uint32_t imm = bits(instr, 20, 31);

	uint32_t imm_top = bits(imm, 5, 11);
	switch (funct3)
	{
	case 0:
		return std::make_unique<ADDI>(rs1, imm, rd);
		break;
	
	case 1:
		//FIXME: need to check top bits in imm are 0
		return std::make_unique<SLLI>(rs1, imm & 0b11111, rd);
		break;
	
	case 2:
		return std::make_unique<SLTI>(rs1, imm, rd);
		break;

	case 3:
		return std::make_unique<SLTIU>(rs1, imm, rd);
		break;

	case 4:
		return std::make_unique<XORI>(rs1, imm, rd);
		break;

	case 5:
		if(imm_top == 0x0u) {
			return std::make_unique<SRLI>(rs1, bits(imm, 0, 4), rd);
		} else if (imm_top == 0x20) {
			return std::make_unique<SRAI>(rs1, bits(imm, 0, 4), rd);
		} else {
			return std::make_unique<UndefInstr>(instr);
		}
		break;

	case 6:
		return std::make_unique<ORI>(rs1, imm, rd);
		break;

	case 7:
		return std::make_unique<ANDI>(rs1, imm, rd);
		break;

	default:
		break;
	}

	return std::make_unique<UndefInstr>(instr);
}

std::unique_ptr<ISA> isa_rv32i(){
	std::unique_ptr<ISA> isa = std::make_unique<ISA>();

	isa.get()->add_instr(0b0010011, instr_gen(op_imm));

	return isa;
}

bool ISA::add_instr(uint32_t opcode, instr_gen f){

	if (this->instrs.count(opcode)){
		return false;
	}
	
	this->instrs.emplace(
		std::make_pair(opcode, f)		
	);

	return true;
}

void InstructionParser::register_isa(std::unique_ptr<ISA> isa) {
	for (auto const& entry : *(isa->get_map())){
		this->instrs.emplace(std::make_pair(entry.first, entry.second));
	}
}

std::unique_ptr<AInstruction> InstructionParser::parse(uint32_t instruction){
	uint32_t opcode = bits(instruction, 0, 6);

	if (this->instrs.count(opcode) == 0) {
		return std::make_unique<UndefInstr>(instruction);
	}

	instr_gen gen = this->instrs.at(opcode);
	
	return gen(instruction);
}
