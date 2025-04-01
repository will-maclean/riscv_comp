#include "instructions.hpp"
#include "cpu.hpp"
#include "utils.hpp"

#include <iostream>
#include <memory>
#include <sstream>

UndefInstr::UndefInstr(RVUnparsedInstr instr):instr(instr){}

InstrResult UndefInstr::execute(CPUThread* thread){
	std::cout << "Unknown instruction: " << this->instr.to_str() << std::endl;

	return InstrResult(0, ExeFlow::ERROR);
}

std::string UndefInstr::to_string(){
	std::stringstream s;
	s << "unknown_instr " << this->instr.to_str();
	return s.str();
}

bool ISA::add_instr(uint8_t opcode, instr_gen f){

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

std::unique_ptr<AInstruction> InstructionParser::parse(RVUnparsedInstr instruction){
	uint8_t opcode = bits(instruction.opcode(), 0, 6);
	if (this->instrs.count(opcode) == 0) {
		return std::make_unique<UndefInstr>(instruction);
	}

	instr_gen gen = this->instrs.at(opcode);
	
	return gen(instruction);
}

int32_t extract_imm_signed32(uint32_t instr, ImmType imm_type){
	int32_t res = 0;

	switch(imm_type){
		case(ImmType::R):
			// R type instructions don't actually 
			// have an immediate section
			return res;
		case(ImmType::I):
			res = (int32_t)sext(bits(instr, 20, 31), 11);
			break;

		case(ImmType::S):
			res = bits(instr, 25, 31);
			res = res << 5;
			res = res | bits(instr, 7, 11);
			res = sext(res, 10);
			break;

		case(ImmType::B):
			res = set_bits(res, 11, 11, bits(instr, 7, 7));
			res = set_bits(res, 1, 4, bits(instr, 8, 11));
			res = set_bits(res, 5, 10, bits(instr, 25, 30));
			res = set_bits(res, 12, 12, bits(instr, 31, 31));
			res = sext(res, 11);
			break;
		case(ImmType::U):
			res = bits(instr, 12, 30) << 12;
			break;
		case(ImmType::J):
			res |= bit(instr, 31) << 19;
			res |= bits(instr, 21, 30) << 1;
			res |= bit(instr, 20) << 10;
			res |= bits(instr, 12, 19) << 11;
			res = sext(res, 19);
			break;
	}

	return res;
}

uint32_t extract_imm_unsigned32(uint32_t instr, ImmType imm_type){
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
			res = set_bits(res, 11, 11, bits(instr, 7, 7));
			res = set_bits(res, 1, 4, bits(instr, 8, 11));
			res = set_bits(res, 5, 10, bits(instr, 25, 30));
			res = set_bits(res, 12, 12, bits(instr, 31, 31));
			break;
		case(ImmType::U):
			res = bits(instr, 12, 31) << 12;
			break;
		case(ImmType::J):
			std::cout << "Unsupport imm_u type: J" << std::endl;
			break;
	}

	return res;
}