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

int32_t extract_imm_signed(uint32_t instr, ImmType imm_type){
	int32_t res = 0;

	switch(imm_type){
		case(ImmType::R):
			// R type instructions don't actually 
			// have an immediate section
			return res;
		case(ImmType::I):
			res = (int32_t)bits(instr, 20, 30);
			break;

		case(ImmType::S):
			res = bits(instr, 25, 30);
			res = res << 5;
			res = res | bits(instr, 7, 11);
			break;

		case(ImmType::B):
			std::cout << "Unsupport imm type: B" << std::endl;
			break;
		case(ImmType::U):
			res = bits(instr, 12, 30) << 12;
			break;
		case(ImmType::J):
			std::cout << "Unsupport imm type: J" << std::endl;
			break;
	}

	if (bit(instr, 31) != POSITIVE_BIT){
		res *= -1;
	}

	return res;
}

uint32_t extract_imm_unsigned(uint32_t instr, ImmType imm_type){
	uint32_t res = 0;

	switch(imm_type){
		case(ImmType::R):
			// R type instructions don't actually 
			// have an immediate section
			return res;
		case(ImmType::I):
			res = bits(instr, 20, 31);
			return res;

		case(ImmType::S):
			res = bits(instr, 25, 31);
			res = res << 5;
			res = res | bits(instr, 7, 11);
			return res;

		case(ImmType::B):
			std::cout << "Unsupport imm type: B" << std::endl;
			break;
		case(ImmType::U):
			res = bits(instr, 12, 31) << 12;
			break;
		case(ImmType::J):
			std::cout << "Unsupport imm type: J" << std::endl;
			break;
	}

	return res;
}