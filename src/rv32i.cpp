#include "rv32i.hpp"
#include "utils.hpp"

#include <sstream>

ADD::ADD(uint32_t reg_a, uint32_t reg_b, uint32_t reg_dest)
	: reg_a(reg_a),
	  reg_b(reg_b),
	  reg_dest(reg_dest),
	  instr_bytes(4){}

ADD::ADD(uint32_t reg_a, uint32_t reg_b, uint32_t reg_dest, uint8_t instr_bytes)
	: reg_a(reg_a),
	  reg_b(reg_b),
	  reg_dest(reg_dest),
	  instr_bytes(instr_bytes){}

InstrResult ADD::execute(CPUThread *thread) {
	thread->get_regs()->set_ri(reg_dest,
							   thread->get_regs()->get_ri(reg_a) + thread->get_regs()->get_ri(this->reg_b));

	return InstrResult(this->instr_bytes);
}

uint32_t ADD::to_instruction() {
	uint32_t res = 0;

	res = set_bits(res, 0, 6, 0b0010011);
	res = set_bits(res, 7, 11, this->reg_dest);
	res = set_bits(res, 12, 14, 0b000);
	res = set_bits(res, 15, 19, this->reg_a);
	res = set_bits(res, 20, 24, this->reg_b);
	res = set_bits(res, 25, 31, 0b0000000);

	return res;
}

std::string ADD::to_string() {
	std::stringstream s;
	s << "add r" << this->reg_dest << ", r" << this->reg_a << ", r" << this->reg_b;

	return s.str();
}

SUB::SUB(uint32_t rs1, uint32_t rs2, uint32_t rsd)
	: rs1(rs1),
	  rs2(rs2),
	  rsd(rsd),
	  instr_bytes(4){}

SUB::SUB(uint32_t rs1, uint32_t rs2, uint32_t rsd, uint8_t instr_bytes)
	: rs1(rs1),
	  rs2(rs2),
	  rsd(rsd),
	  instr_bytes(instr_bytes){}

InstrResult SUB::execute(CPUThread *thread) {
	thread->get_regs()->set_ri(this->rsd,
							   thread->get_regs()->get_ri(rs1) - thread->get_regs()->get_ri(rs2));

	return InstrResult(this->instr_bytes);
}

std::string SUB::to_string() {
	std::stringstream s;
	s << "sub r" << this->rsd << ", r" << this->rs1 << ", r" << this->rs2;

	return s.str();
}

ADDI::ADDI(uint32_t reg_a, int32_t imm, uint32_t reg_dest)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest),
	  instr_bytes(4){}

ADDI::ADDI(uint32_t reg_a, int32_t imm, uint32_t reg_dest, uint8_t instr_bytes)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest),
	  instr_bytes(instr_bytes){}

InstrResult ADDI::execute(CPUThread *thread) {
	thread->get_regs()->set_ri(this->reg_dest,
							   thread->get_regs()->get_ri(this->reg_a) + this->imm);

	return InstrResult(this->instr_bytes);
}

uint32_t ADDI::to_instruction() {
	uint32_t res = 0;

	res = set_bits(res, 0, 6, 0b0010011);
	res = set_bits(res, 7, 11, this->reg_dest);
	res = set_bits(res, 12, 14, 0b000);
	res = set_bits(res, 15, 19, this->reg_a);
	res = set_bits(res, 20, 31, this->imm);

	return res;
}

std::string ADDI::to_string() {
	std::stringstream s;
	s << "addi r" << this->reg_dest << ", r" << this->reg_a << ", " << this->imm;

	return s.str();
}

SLLI::SLLI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest),
	  instr_bytes(4){}

SLLI::SLLI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest, uint8_t instr_bytes)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest),
	  instr_bytes(instr_bytes){}

InstrResult SLLI::execute(CPUThread *thread) {
	thread->get_regs()->set_ri(this->reg_dest,
							   thread->get_regs()->get_ri(this->reg_a) << this->imm);

	return InstrResult(this->instr_bytes);
}
std::string SLLI::to_string() {
	std::stringstream s;
	s << "slli r" << this->reg_dest << ", r" << this->reg_a << ", " << this->imm;

	return s.str();
}
SLTI::SLTI(uint32_t reg_a, int32_t imm, uint32_t reg_dest)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest),
	  instr_bytes(4){}

SLTI::SLTI(uint32_t reg_a, int32_t imm, uint32_t reg_dest, uint8_t instr_bytes)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest),
	  instr_bytes(instr_bytes){}

InstrResult SLTI::execute(CPUThread *thread) {
	thread->get_regs()->set_ri(this->reg_dest,
							   thread->get_regs()->get_ri(this->reg_a) < this->imm ? 1 : 0);

	return InstrResult(this->instr_bytes);
}

uint32_t SLTI::to_instruction() {
	uint32_t res = 0;

	res = set_bits(res, 0, 6, 0b0010011);
	res = set_bits(res, 7, 11, this->reg_dest);
	res = set_bits(res, 12, 14, 0b010);
	res = set_bits(res, 15, 19, this->reg_a);
	res = set_bits(res, 20, 31, this->imm);

	return res;
}

std::string SLTI::to_string() {
	std::stringstream s;
	s << "slti r" << this->reg_dest << ", r" << this->reg_a << ", " << this->imm;

	return s.str();
}

SLTIU::SLTIU(uint32_t reg_a, uint32_t imm, uint32_t reg_dest)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest),
	  instr_bytes(4){}

SLTIU::SLTIU(uint32_t reg_a, uint32_t imm, uint32_t reg_dest, uint8_t instr_bytes)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest),
	  instr_bytes(instr_bytes){}

InstrResult SLTIU::execute(CPUThread *thread) {
	thread->get_regs()->set_ri(this->reg_dest,
							   (uint32_t)thread->get_regs()->get_ri(this->reg_a) < this->imm ? 1 : 0);

	return InstrResult(this->instr_bytes);
}

std::string SLTIU::to_string() {
	std::stringstream s;
	s << "sltiu r" << this->reg_dest << ", r" << this->reg_a << ", " << this->imm;

	return s.str();
}

SLTU::SLTU(uint32_t rs1, uint32_t rs2, uint32_t rsd)
	: rs1(rs1),
	  rs2(rs2),
	  rsd(rsd),
	  instr_bytes(4){}

SLTU::SLTU(uint32_t rs1, uint32_t rs2, uint32_t rsd, uint8_t instr_bytes)
	: rs1(rs1),
	  rs2(rs2),
	  rsd(rsd),
	  instr_bytes(instr_bytes){}

InstrResult SLTU::execute(CPUThread *thread) {
	uint32_t a = thread->get_regs()->get_ri(this->rs1);
	uint32_t b = thread->get_regs()->get_ri(this->rs2);
	thread->get_regs()->set_ri(this->rsd, a < b ? 1 : 0);

	return InstrResult(this->instr_bytes);
}

std::string SLTU::to_string() {
	std::stringstream s;
	s << "sltu r" << this->rsd << ", r" << this->rs1 << ", r" << this->rs2;

	return s.str();
}
SLT::SLT(uint32_t rs1, uint32_t rs2, uint32_t rsd)
	: rs1(rs1),
	  rs2(rs2),
	  rsd(rsd),
	  instr_bytes(4){}

SLT::SLT(uint32_t rs1, uint32_t rs2, uint32_t rsd, uint8_t instr_bytes)
	: rs1(rs1),
	  rs2(rs2),
	  rsd(rsd),
	  instr_bytes(instr_bytes){}

InstrResult SLT::execute(CPUThread *thread) {
	int32_t a = thread->get_regs()->get_ri(this->rs1);
	int32_t b = thread->get_regs()->get_ri(this->rs2);
	thread->get_regs()->set_ri(this->rsd, a < b ? 1 : 0);

	return InstrResult(this->instr_bytes);
}

std::string SLT::to_string() {
	std::stringstream s;
	s << "slt r" << this->rsd << ", r" << this->rs1 << ", r" << this->rs2;

	return s.str();
}

XORI::XORI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest),
	  instr_bytes(4){}

XORI::XORI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest, uint8_t instr_bytes)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest),
	  instr_bytes(instr_bytes){}

InstrResult XORI::execute(CPUThread *thread) {
	thread->get_regs()->set_ri(this->reg_dest,
							   thread->get_regs()->get_ri(this->reg_a) ^ this->imm);

	return InstrResult(this->instr_bytes);
}

std::string XORI::to_string() {
	std::stringstream s;
	s << "xori r" << this->reg_dest << ", r" << this->reg_a << ", " << this->imm;

	return s.str();
}
ANDI::ANDI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest),
	  instr_bytes(4){}

ANDI::ANDI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest, uint8_t instr_bytes)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest),
	  instr_bytes(instr_bytes){}

InstrResult ANDI::execute(CPUThread *thread) {
	thread->get_regs()->set_ri(this->reg_dest,
							   thread->get_regs()->get_ri(this->reg_a) & this->imm);

	return InstrResult(this->instr_bytes);
}

std::string ANDI::to_string() {
	std::stringstream s;
	s << "andi r" << this->reg_dest << ", r" << this->reg_a << ", " << this->imm;

	return s.str();
}
SRLI::SRLI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest),
	  instr_bytes(4){}

SRLI::SRLI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest, uint8_t instr_bytes)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest),
	  instr_bytes(instr_bytes){}

InstrResult SRLI::execute(CPUThread *thread) {
	thread->get_regs()->set_ri(this->reg_dest,
							   thread->get_regs()->get_ri(this->reg_a) >> this->imm);

	return InstrResult(this->instr_bytes);
}

std::string SRLI::to_string() {
	std::stringstream s;
	s << "srli r" << this->reg_dest << ", r" << this->reg_a << ", " << this->imm;

	return s.str();
}
SRA::SRA(uint32_t rs1, uint32_t rs2, uint32_t rsd)
	: rs1(rs1),
	  rs2(rs2),
	  rsd(rsd),
	  instr_bytes(4){}

SRA::SRA(uint32_t rs1, uint32_t rs2, uint32_t rsd, uint8_t instr_bytes)
	: rs1(rs1),
	  rs2(rs2),
	  rsd(rsd),
	  instr_bytes(instr_bytes){}

InstrResult SRA::execute(CPUThread *thread) {
	uint32_t shift = thread->get_regs()->get_ri(this->rs2);
	int32_t res = thread->get_regs()->get_ri(this->rs1) >> shift;

	res = sext(res, 32 - shift);

	thread->get_regs()->set_ri(this->rsd, res);

	return InstrResult(this->instr_bytes);
}

std::string SRA::to_string() {
	std::stringstream s;
	s << "sra r" << this->rsd << ", r" << this->rs1 << ", r" << this->rs2;

	return s.str();
}
SRAI::SRAI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest),
	  instr_bytes(4){}

SRAI::SRAI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest, uint8_t instr_bytes)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest),
	  instr_bytes(instr_bytes){}

InstrResult SRAI::execute(CPUThread *thread) {
	int32_t res = thread->get_regs()->get_ri(this->reg_a) >> this->imm;

	res = sext(res, 32 - this->imm);

	thread->get_regs()->set_ri(this->reg_dest, res);

	return InstrResult(this->instr_bytes);
}

std::string SRAI::to_string() {
	std::stringstream s;
	s << "srai r" << this->reg_dest << ", r" << this->reg_a << ", " << this->imm;

	return s.str();
}
ORI::ORI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest),
	  instr_bytes(4){}

ORI::ORI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest, uint8_t instr_bytes)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest),
	  instr_bytes(instr_bytes){}

InstrResult ORI::execute(CPUThread *thread) {
	thread->get_regs()->set_ri(this->reg_dest,
							   thread->get_regs()->get_ri(this->reg_a) | this->imm);

	return InstrResult(this->instr_bytes);
}

std::string ORI::to_string() {
	std::stringstream s;
	s << "ori r" << this->reg_dest << ", r" << this->reg_a << ", " << this->imm;

	return s.str();
}

XOR::XOR(uint32_t rs1, uint32_t rs2, uint32_t rsd) : rs1(rs1),
													 rs2(rs2),
													 rsd(rsd),
													 instr_bytes(4){}

XOR::XOR(uint32_t rs1, uint32_t rs2, uint32_t rsd, uint8_t instr_bytes) : rs1(rs1),
																		  rs2(rs2),
																		  rsd(rsd),
																		  instr_bytes(instr_bytes){}

InstrResult XOR::execute(CPUThread *thread) {
	thread->get_regs()->set_ri(this->rsd,
							   thread->get_regs()->get_ri(this->rs1) ^ thread->get_regs()->get_ri(this->rs2));

	return InstrResult(this->instr_bytes);
}

std::string XOR::to_string() {
	std::stringstream s;
	s << "xor r" << this->rsd << ", r" << this->rs1 << ", r" << this->rs2;

	return s.str();
}
OR::OR(uint32_t rs1, uint32_t rs2, uint32_t rsd) : rs1(rs1),
												   rs2(rs2),
												   rsd(rsd),
												   instr_bytes(4){}

OR::OR(uint32_t rs1, uint32_t rs2, uint32_t rsd, uint8_t instr_bytes) : rs1(rs1),
																		rs2(rs2),
																		rsd(rsd),
																		instr_bytes(instr_bytes){}

InstrResult OR::execute(CPUThread *thread) {
	thread->get_regs()->set_ri(this->rsd,
							   thread->get_regs()->get_ri(this->rs1) | thread->get_regs()->get_ri(this->rs2));

	return InstrResult(this->instr_bytes);
}

std::string OR::to_string() {
	std::stringstream s;
	s << "or r" << this->rsd << ", r" << this->rs1 << ", r" << this->rs2;

	return s.str();
}
AND::AND(uint32_t rs1, uint32_t rs2, uint32_t rsd) : rs1(rs1),
													 rs2(rs2),
													 rsd(rsd),
													 instr_bytes(4){}

AND::AND(uint32_t rs1, uint32_t rs2, uint32_t rsd, uint8_t instr_bytes) : rs1(rs1),
																		  rs2(rs2),
																		  rsd(rsd),
																		  instr_bytes(instr_bytes){}

InstrResult AND::execute(CPUThread *thread) {
	thread->get_regs()->set_ri(this->rsd,
							   thread->get_regs()->get_ri(this->rs1) & thread->get_regs()->get_ri(this->rs2));

	return InstrResult(this->instr_bytes);
}

std::string AND::to_string() {
	std::stringstream s;
	s << "and r" << this->rsd << ", r" << this->rs1 << ", r" << this->rs2;

	return s.str();
}
SRL::SRL(uint32_t rs1, uint32_t rs2, uint32_t rsd) : rs1(rs1),
													 rs2(rs2),
													 rsd(rsd),
													 instr_bytes(4){}

SRL::SRL(uint32_t rs1, uint32_t rs2, uint32_t rsd, uint8_t instr_bytes) : rs1(rs1),
																		  rs2(rs2),
																		  rsd(rsd),
																		  instr_bytes(instr_bytes){}

InstrResult SRL::execute(CPUThread *thread) {
	thread->get_regs()->set_ri(this->rsd,
							   thread->get_regs()->get_ri(this->rs1) >> thread->get_regs()->get_ri(this->rs2));

	return InstrResult(this->instr_bytes);
}

std::string SRL::to_string() {
	std::stringstream s;
	s << "srl r" << this->rsd << ", r" << this->rs1 << ", r" << this->rs2;

	return s.str();
}
SLL::SLL(uint32_t rs1, uint32_t rs2, uint32_t rsd) : rs1(rs1),
													 rs2(rs2),
													 rsd(rsd),
													 instr_bytes(4){}

SLL::SLL(uint32_t rs1, uint32_t rs2, uint32_t rsd, uint8_t instr_bytes) : rs1(rs1),
																		  rs2(rs2),
																		  rsd(rsd),
																		  instr_bytes(instr_bytes){}

InstrResult SLL::execute(CPUThread *thread) {
	thread->get_regs()->set_ri(this->rsd,
							   thread->get_regs()->get_ri(this->rs1) << thread->get_regs()->get_ri(this->rs2));

	return InstrResult(this->instr_bytes);
}

std::string SLL::to_string() {
	std::stringstream s;
	s << "sll r" << this->rsd << ", r" << this->rs1 << ", r" << this->rs2;

	return s.str();
}
LUI::LUI(uint32_t imm, uint32_t rsd) : imm(imm), rsd(rsd),
									   instr_bytes(4) {}

LUI::LUI(uint32_t imm, uint32_t rsd, uint8_t instr_bytes) : imm(imm), rsd(rsd),
															instr_bytes(instr_bytes) {}

InstrResult LUI::execute(CPUThread *thread) {
	thread->get_regs()->set_ri(this->rsd, this->imm);

	return InstrResult(this->instr_bytes);
}
std::string LUI::to_string() {
	std::stringstream s;
	s << "lui r" << this->rsd << ", " << this->imm;

	return s.str();
}

AUIPC::AUIPC(int32_t imm, uint32_t rsd) : imm(imm), rsd(rsd),
										  instr_bytes(4) {}

AUIPC::AUIPC(int32_t imm, uint32_t rsd, uint8_t instr_bytes) : imm(imm), rsd(rsd),
															   instr_bytes(instr_bytes) {}

InstrResult AUIPC::execute(CPUThread *thread) {
	thread->get_regs()->set_ri(this->rsd, thread->get_regs()->pc + this->imm);

	return InstrResult(this->instr_bytes);
}

std::string AUIPC::to_string() {
	std::stringstream s;
	s << "auipc r" << this->rsd << ", " << this->imm;

	return s.str();
}

BEQ::BEQ(uint32_t rs1, uint32_t rs2, int32_t imm) : rs1(rs1), rs2(rs2), imm(imm),
													instr_bytes(4){}

BEQ::BEQ(uint32_t rs1, uint32_t rs2, int32_t imm, uint8_t instr_bytes) : rs1(rs1), rs2(rs2), imm(imm),
																		 instr_bytes(instr_bytes){}

InstrResult BEQ::execute(CPUThread *thread) {
	if (thread->get_regs()->get_ri(this->rs1) == thread->get_regs()->get_ri(this->rs2))
	{
		return InstrResult(this->imm);
	}

	return InstrResult(this->instr_bytes);
}

std::string BEQ::to_string() {
	std::stringstream s;
	s << "beq r" << this->rs1 << ", r" << this->rs2 << ", " << this->imm;

	return s.str();
}
BNE::BNE(uint32_t rs1, uint32_t rs2, int32_t imm) : rs1(rs1), rs2(rs2), imm(imm),
													instr_bytes(4){}

BNE::BNE(uint32_t rs1, uint32_t rs2, int32_t imm, uint8_t instr_bytes) : rs1(rs1), rs2(rs2), imm(imm),
																		 instr_bytes(instr_bytes){}

InstrResult BNE::execute(CPUThread *thread) {
	if (thread->get_regs()->get_ri(this->rs1) != thread->get_regs()->get_ri(this->rs2))
	{
		return InstrResult(this->imm);
	}

	return InstrResult(this->instr_bytes);
}

std::string BNE::to_string() {
	std::stringstream s;
	s << "bne r" << this->rs1 << ", r" << this->rs2 << ", " << this->imm;

	return s.str();
}
BLT::BLT(uint32_t rs1, uint32_t rs2, int32_t imm) : rs1(rs1), rs2(rs2), imm(imm),
													instr_bytes(4){}

BLT::BLT(uint32_t rs1, uint32_t rs2, int32_t imm, uint8_t instr_bytes) : rs1(rs1), rs2(rs2), imm(imm),
																		 instr_bytes(instr_bytes){}

InstrResult BLT::execute(CPUThread *thread) {
	if (thread->get_regs()->get_ri(this->rs1) < thread->get_regs()->get_ri(this->rs2))
	{
		return InstrResult(this->imm);
	}

	return InstrResult(this->instr_bytes);
}

std::string BLT::to_string() {
	std::stringstream s;
	s << "blt r" << this->rs1 << ", r" << this->rs2 << ", " << this->imm;

	return s.str();
}
BGT::BGT(uint32_t rs1, uint32_t rs2, int32_t imm) : rs1(rs1), rs2(rs2), imm(imm),
													instr_bytes(4){}

BGT::BGT(uint32_t rs1, uint32_t rs2, int32_t imm, uint8_t instr_bytes) : rs1(rs1), rs2(rs2), imm(imm),
																		 instr_bytes(instr_bytes){}

InstrResult BGT::execute(CPUThread *thread) {
	if (thread->get_regs()->get_ri(this->rs1) > thread->get_regs()->get_ri(this->rs2))
	{
		return InstrResult(this->imm);
	}

	return InstrResult(this->instr_bytes);
}

std::string BGT::to_string() {
	std::stringstream s;
	s << "bgt r" << this->rs1 << ", r" << this->rs2 << ", " << this->imm;

	return s.str();
}
BGE::BGE(uint32_t rs1, uint32_t rs2, int32_t imm) : rs1(rs1), rs2(rs2), imm(imm),
													instr_bytes(4){}

BGE::BGE(uint32_t rs1, uint32_t rs2, int32_t imm, uint8_t instr_bytes) : rs1(rs1), rs2(rs2), imm(imm),
																		 instr_bytes(instr_bytes){}

InstrResult BGE::execute(CPUThread *thread) {
	if (thread->get_regs()->get_ri(this->rs1) >= thread->get_regs()->get_ri(this->rs2))
	{
		return InstrResult(this->imm);
	}

	return InstrResult(this->instr_bytes);
}

std::string BGE::to_string() {
	std::stringstream s;
	s << "bge r" << this->rs1 << ", r" << this->rs2 << ", " << this->imm;

	return s.str();
}
BLE::BLE(uint32_t rs1, uint32_t rs2, int32_t imm) : rs1(rs1), rs2(rs2), imm(imm),
													instr_bytes(4){}

BLE::BLE(uint32_t rs1, uint32_t rs2, int32_t imm, uint8_t instr_bytes) : rs1(rs1), rs2(rs2), imm(imm),
																		 instr_bytes(instr_bytes){}

InstrResult BLE::execute(CPUThread *thread) {
	if (thread->get_regs()->get_ri(this->rs1) <= thread->get_regs()->get_ri(this->rs2))
	{
		return InstrResult(this->imm);
	}

	return InstrResult(this->instr_bytes);
}

std::string BLE::to_string() {
	std::stringstream s;
	s << "ble r" << this->rs1 << ", r" << this->rs2 << ", " << this->imm;

	return s.str();
}
BLTU::BLTU(uint32_t rs1, uint32_t rs2, uint32_t imm) : rs1(rs1), rs2(rs2), imm(imm),
													   instr_bytes(4){}

BLTU::BLTU(uint32_t rs1, uint32_t rs2, uint32_t imm, uint8_t instr_bytes) : rs1(rs1), rs2(rs2), imm(imm),
																			instr_bytes(instr_bytes){}

InstrResult BLTU::execute(CPUThread *thread) {
	if (thread->get_regs()->get_ri(this->rs1) < thread->get_regs()->get_ri(this->rs2))
	{
		return InstrResult(this->imm);
	}

	return InstrResult(this->instr_bytes);
}

std::string BLTU::to_string() {
	std::stringstream s;
	s << "bltu r" << this->rs1 << ", r" << this->rs2 << ", " << this->imm;

	return s.str();
}
BGEU::BGEU(uint32_t rs1, uint32_t rs2, uint32_t imm) : rs1(rs1), rs2(rs2), imm(imm),
													   instr_bytes(4){}

BGEU::BGEU(uint32_t rs1, uint32_t rs2, uint32_t imm, uint8_t instr_bytes) : rs1(rs1), rs2(rs2), imm(imm),
																			instr_bytes(instr_bytes){}
InstrResult BGEU::execute(CPUThread *thread) {
	if (thread->get_regs()->get_ri(this->rs1) >= thread->get_regs()->get_ri(this->rs2))
	{
		return InstrResult(this->imm);
	}

	return InstrResult(this->instr_bytes);
}

std::string BGEU::to_string() {
	std::stringstream s;
	s << "bgeu r" << this->rs1 << ", r" << this->rs2 << ", " << this->imm;

	return s.str();
}
LOAD::LOAD(uint32_t base, LoadType type, uint32_t dest, int32_t offset)
	: base(base),
	  type(type),
	  dest(dest),
	  offset(offset),
	  instr_bytes(4){}

LOAD::LOAD(uint32_t base, LoadType type, uint32_t dest, int32_t offset, uint8_t instr_bytes)
	: base(base),
	  type(type),
	  dest(dest),
	  offset(offset),
	  instr_bytes(instr_bytes){}

InstrResult LOAD::execute(CPUThread *thread) {
	uint32_t read_addr = (uint32_t)(thread->get_regs()->get_ri(this->base) + this->offset);

	int32_t store_val = 0;
	switch (this->type)
	{
	case LoadType::LB:
		store_val = sext(thread->get_ram()->get_b(read_addr), 7);

		break;
	case LoadType::LBU:
		store_val = thread->get_ram()->get_b(read_addr);
		break;
	case LoadType::LH:
		store_val = sext(thread->get_ram()->get_h(read_addr), 15);
		break;
	case LoadType::LHU:
		store_val = thread->get_ram()->get_h(read_addr);
		break;
	case LoadType::LW:
		store_val = thread->get_ram()->get_w(read_addr);
		break;
	}

	thread->get_regs()->set_ri(this->dest, store_val);

	return InstrResult(this->instr_bytes);
}

std::string LOAD::to_string() {
	std::stringstream s;

	switch (this->type)
	{
	case LoadType::LB:
		s << "lb ";
		break;
	case LoadType::LBU:
		s << "lbu ";
		break;
	case LoadType::LH:
		s << "lh ";
		break;
	case LoadType::LHU:
		s << "lhu ";
		break;
	case LoadType::LW:
		s << "lw ";
		break;
	}

	s << "r" << this->dest << ", (" << this->offset << ")r" << this->base;

	return s.str();
}
STORE::STORE(uint32_t src, uint32_t base, StoreType type, int32_t offset)
	: src(src),
	  base(base),
	  type(type),
	  offset(offset),
	  instr_bytes(4){}

STORE::STORE(uint32_t src, uint32_t base, StoreType type, int32_t offset, uint8_t instr_bytes)
	: src(src),
	  base(base),
	  type(type),
	  offset(offset),
	  instr_bytes(instr_bytes){}

InstrResult STORE::execute(CPUThread *thread) {
	uint32_t reg_val = thread->get_regs()->get_ri(this->src);

	uint32_t write_addr = (uint32_t)(thread->get_regs()->get_ri(this->base) + this->offset);

	switch (this->type)
	{
	case StoreType::SB:
		thread->get_ram()->set_b(write_addr, reg_val);
		break;
	case StoreType::SH:
		thread->get_ram()->set_h(write_addr, reg_val);
		break;
	case StoreType::SW:
		thread->get_ram()->set_w(write_addr, reg_val);
		break;
	}

	return InstrResult(this->instr_bytes);
}
std::string STORE::to_string() {
	std::stringstream s;

	switch (this->type)
	{
	case StoreType::SB:
		s << "sb ";
		break;
	case StoreType::SH:
		s << "sh ";
		break;
	case StoreType::SW:
		s << "sw ";
		break;
	}

	s << "r" << this->src << ", (" << this->offset << ")r" << this->base;

	return s.str();
}

JAL::JAL(uint32_t rd, int32_t imm) : rd(rd), imm(imm) {}

JAL::JAL(uint32_t rd, int32_t imm, int32_t instr_bytes) : rd(rd), imm(imm), instr_bytes(instr_bytes) {}

InstrResult JAL::execute(CPUThread *thread) {
	thread->get_regs()->set_ri(this->rd, thread->get_regs()->pc + this->instr_bytes);

	return InstrResult(this->imm);
}

std::string JAL::to_string() {
	std::stringstream s;
	s << "jal r" << this->rd << ", " << this->imm;

	return s.str();
}
JALR::JALR(uint32_t rs1, uint32_t rd, int32_t imm)
	: rs1(rs1), rd(rd), imm(imm), instr_bytes(4) {}

JALR::JALR(uint32_t rs1, uint32_t rd, int32_t imm, uint8_t instr_bytes)
	: rs1(rs1), rd(rd), imm(imm), instr_bytes(instr_bytes) {}

InstrResult JALR::execute(CPUThread *thread) {
	thread->get_regs()->set_ri(this->rd, thread->get_regs()->pc + this->instr_bytes);

	int32_t offset = this->imm + thread->get_regs()->get_ri(this->rs1) - thread->get_regs()->pc;
	offset &= ~1;

	return InstrResult(offset);
}

std::string JALR::to_string() {
	std::stringstream s;
	s << "jalr r" << this->rd << ", r" << this->rs1 << ", " << this->imm;

	return s.str();
}

FENCE::FENCE()
	: instr_bytes(4){}

FENCE::FENCE(uint8_t instr_bytes)
	: instr_bytes(instr_bytes){}

InstrResult FENCE::execute(CPUThread *thread) {
	std::cout << "Fence? Don't ask me" << std::endl;
	return InstrResult(this->instr_bytes);
}

std::string FENCE::to_string() {
	return std::string("fence");
}

ECALL::ECALL()
	: instr_bytes(4) {}
ECALL::ECALL(uint8_t instr_bytes)
	: instr_bytes(instr_bytes) {}

InstrResult ECALL::execute(CPUThread *thread) {
	std::cout << "ECALL" << std::endl;
	return InstrResult(this->instr_bytes);
}

std::string ECALL::to_string() {
	return std::string("ecall");
}

EBREAK::EBREAK()
	: instr_bytes(4){}

	EBREAK::EBREAK(uint8_t instr_bytes)
	: instr_bytes(instr_bytes){}

InstrResult EBREAK::execute(CPUThread *thread) {
	std::cout << "EBREAK" << std::endl;
	return InstrResult(4, ExeFlow::STOP);
}

std::string EBREAK::to_string() {
	return std::string("ebreak");
}
std::unique_ptr<AInstruction> rv32i_op_imm(RVUnparsedInstr unparsed_instr) {
	if (unparsed_instr.type != RVUnparsedInstrType::INSTR32)
	{
		return std::make_unique<UndefInstr>(unparsed_instr);
	}

	uint32_t instr = unparsed_instr.instr.instr_32;
	uint32_t rd = bits(instr, 7, 11);
	uint32_t funct3 = bits(instr, 12, 14);
	uint32_t rs1 = bits(instr, 15, 19);
	int32_t imm_s = extract_imm_signed32(instr, ImmType::I);
	uint32_t imm_u = extract_imm_unsigned32(instr, ImmType::I);

	uint32_t imm_top = bits(imm_u, 5, 11);
	switch (funct3)
	{
	case 0:
		return std::make_unique<ADDI>(rs1, imm_s, rd);

	case 1:
		// FIXME: need to check top bits in imm are 0
		return std::make_unique<SLLI>(rs1, imm_u & 0b11111, rd);
	case 2:
		return std::make_unique<SLTI>(rs1, imm_s, rd);
	case 3:
		return std::make_unique<SLTIU>(rs1, imm_u, rd);
	case 4:
		return std::make_unique<XORI>(rs1, imm_u, rd);
	case 5:
		if (imm_top == 0x0u)
		{
			return std::make_unique<SRLI>(rs1, bits(imm_u, 0, 4), rd);
		}
		else if (imm_top == 0x20)
		{
			return std::make_unique<SRAI>(rs1, bits(imm_u, 0, 4), rd);
		}
		else
		{
			return std::make_unique<UndefInstr>(unparsed_instr);
		}
	case 6:
		return std::make_unique<ORI>(rs1, imm_u, rd);
	case 7:
		return std::make_unique<ANDI>(rs1, imm_u, rd);
	default:
		return std::make_unique<UndefInstr>(unparsed_instr);
	}

	return std::make_unique<UndefInstr>(unparsed_instr);
}

std::unique_ptr<AInstruction> rv32i_op(RVUnparsedInstr unparsed_instr) {
	if (unparsed_instr.type != RVUnparsedInstrType::INSTR32)
	{
		return std::make_unique<UndefInstr>(unparsed_instr);
	}

	uint32_t instr = unparsed_instr.instr.instr_32;
	uint32_t rd = bits(instr, 7, 11);
	uint32_t f3 = bits(instr, 12, 14);
	uint32_t rs1 = bits(instr, 15, 19);
	uint32_t rs2 = bits(instr, 20, 24);
	uint32_t f7 = bits(instr, 25, 31);

	switch (f7)
	{
	case 0x0:
		switch (f3)
		{
		case 0:
			return std::make_unique<ADD>(rs1, rs2, rd);
		case 1:
			return std::make_unique<SLL>(rs1, rs2, rd);
		case 2:
			return std::make_unique<SLT>(rs1, rs2, rd);
		case 3:
			return std::make_unique<SLTU>(rs1, rs2, rd);
		case 4:
			return std::make_unique<XOR>(rs1, rs2, rd);
		case 5:
			return std::make_unique<SRL>(rs1, rs2, rd);
		case 6:
			return std::make_unique<OR>(rs1, rs2, rd);
		case 7:
			return std::make_unique<AND>(rs1, rs2, rd);
		default:
			return std::make_unique<UndefInstr>(unparsed_instr);
		}
	case 0x20:
		switch (f3)
		{
		case 0:
			return std::make_unique<SUB>(rs1, rs2, rd);
		case 5:
			return std::make_unique<SRA>(rs1, rs2, rd);
		default:
			return std::make_unique<UndefInstr>(unparsed_instr);
		}
	default:
		return std::make_unique<UndefInstr>(unparsed_instr);
	}
}

std::unique_ptr<AInstruction> rv32i_lui(RVUnparsedInstr unparsed_instr) {
	if (unparsed_instr.type != RVUnparsedInstrType::INSTR32)
	{
		return std::make_unique<UndefInstr>(unparsed_instr);
	}

	uint32_t instr = unparsed_instr.instr.instr_32;
	return std::make_unique<LUI>(
		bits(instr, 21, 31),
		bits(instr, 7, 11));
}

std::unique_ptr<AInstruction> rv32i_auipc(RVUnparsedInstr unparsed_instr) {
	if (unparsed_instr.type != RVUnparsedInstrType::INSTR32)
	{
		return std::make_unique<UndefInstr>(unparsed_instr);
	}

	uint32_t instr = unparsed_instr.instr.instr_32;

	return std::make_unique<AUIPC>(
		bits(instr, 21, 31),
		bits(instr, 7, 11));
}

std::unique_ptr<AInstruction> rv32i_jal(RVUnparsedInstr unparsed_instr) {
	if (unparsed_instr.type != RVUnparsedInstrType::INSTR32)
	{
		return std::make_unique<UndefInstr>(unparsed_instr);
	}

	uint32_t instr = unparsed_instr.instr.instr_32;
	return std::make_unique<JAL>(
		bits(instr, 7, 11),
		extract_imm_signed32(instr, ImmType::J));
}

std::unique_ptr<AInstruction> rv32i_jalr(RVUnparsedInstr unparsed_instr) {
	if (unparsed_instr.type != RVUnparsedInstrType::INSTR32)
	{
		return std::make_unique<UndefInstr>(unparsed_instr);
	}

	uint32_t instr = unparsed_instr.instr.instr_32;

	return std::make_unique<JALR>(
		bits(instr, 15, 19),
		bits(instr, 7, 11),
		extract_imm_signed32(instr, ImmType::I));
}

std::unique_ptr<AInstruction> rv32i_branch(RVUnparsedInstr unparsed_instr) {
	if (unparsed_instr.type != RVUnparsedInstrType::INSTR32)
	{
		return std::make_unique<UndefInstr>(unparsed_instr);
	}

	uint32_t instr = unparsed_instr.instr.instr_32;
	uint32_t f3 = bits(instr, 12, 14);
	uint32_t rs1 = bits(instr, 15, 19);
	uint32_t rs2 = bits(instr, 20, 24);
	int32_t imm_s = extract_imm_signed32(instr, ImmType::B);
	uint32_t imm_u = extract_imm_unsigned32(instr, ImmType::B);

	switch (f3)
	{
	case 0:
		return std::make_unique<BEQ>(rs1, rs2, imm_s);
	case 1:
		return std::make_unique<BNE>(rs1, rs2, imm_s);
	case 4:
		return std::make_unique<BLT>(rs1, rs2, imm_s);
	case 5:
		return std::make_unique<BGE>(rs1, rs2, imm_s);
	case 6:
		return std::make_unique<BLTU>(rs1, rs2, imm_u);
	case 7:
		return std::make_unique<BGEU>(rs1, rs2, imm_u);
	default:
		return std::make_unique<UndefInstr>(unparsed_instr);
	}
}

std::unique_ptr<AInstruction> rv32i_load(RVUnparsedInstr unparsed_instr) {
	if (unparsed_instr.type != RVUnparsedInstrType::INSTR32)
	{
		return std::make_unique<UndefInstr>(unparsed_instr);
	}

	uint32_t instr = unparsed_instr.instr.instr_32;
	LoadType type;
	switch (bits(instr, 12, 14))
	{
	case 0:
		type = LoadType::LB;
		break;
	case 1:
		type = LoadType::LH;
		break;
	case 2:
		type = LoadType::LW;
		break;
	case 4:
		type = LoadType::LBU;
		break;
	case 5:
		type = LoadType::LHU;
		break;
	default:
		return std::make_unique<UndefInstr>(unparsed_instr);
	}

	return std::make_unique<LOAD>(
		bits(instr, 15, 19), // rs1
		type,
		bits(instr, 7, 11), // rd
		extract_imm_signed32(instr, ImmType::I));
}
std::unique_ptr<AInstruction> rv32i_store(RVUnparsedInstr unparsed_instr) {
	if (unparsed_instr.type != RVUnparsedInstrType::INSTR32)
	{
		return std::make_unique<UndefInstr>(unparsed_instr);
	}

	uint32_t instr = unparsed_instr.instr.instr_32;
	StoreType type;
	switch (bits(instr, 12, 14))
	{
	case 0:
		type = StoreType::SB;
		break;
	case 1:
		type = StoreType::SH;
		break;
	case 2:
		type = StoreType::SW;
		break;
	default:
		return std::make_unique<UndefInstr>(unparsed_instr);
	}

	return std::make_unique<STORE>(
		bits(instr, 20, 24), // rs2 (src)
		bits(instr, 15, 19), // rs1 (base)
		type,
		extract_imm_signed32(instr, ImmType::S));
}

std::unique_ptr<AInstruction> rv32i_misc_mem(RVUnparsedInstr unparsed_instr) {
	if (unparsed_instr.type != RVUnparsedInstrType::INSTR32)
	{
		return std::make_unique<UndefInstr>(unparsed_instr);
	}
	return std::make_unique<FENCE>();
}

std::unique_ptr<AInstruction> rv32i_system(RVUnparsedInstr unparsed_instr) {
	if (unparsed_instr.type != RVUnparsedInstrType::INSTR32)
	{
		return std::make_unique<UndefInstr>(unparsed_instr);
	}
	uint32_t instr = unparsed_instr.instr.instr_32;
	uint32_t non_op = bits(instr, 7, 31);

	if (non_op == 0x0)
	{
		return std::make_unique<ECALL>();
	}
	else if (non_op == 0x2000)
	{
		return std::make_unique<EBREAK>();
	}

	return std::make_unique<UndefInstr>(unparsed_instr);
}
std::unique_ptr<ISA> isa_rv32i() {
	std::unique_ptr<ISA> isa = std::make_unique<ISA>();

	isa.get()->add_instr(0b0000011, instr_gen(rv32i_load));
	isa.get()->add_instr(0b0001111, instr_gen(rv32i_misc_mem));
	isa.get()->add_instr(0b0010011, instr_gen(rv32i_op_imm));
	isa.get()->add_instr(0b0010111, instr_gen(rv32i_auipc));
	isa.get()->add_instr(0b0100011, instr_gen(rv32i_store));
	isa.get()->add_instr(0b0110011, instr_gen(rv32i_op));
	isa.get()->add_instr(0b0110111, instr_gen(rv32i_lui));
	isa.get()->add_instr(0b1101111, instr_gen(rv32i_jal));
	isa.get()->add_instr(0b1100011, instr_gen(rv32i_branch));
	isa.get()->add_instr(0b1100111, instr_gen(rv32i_jalr));
	isa.get()->add_instr(0b1110011, instr_gen(rv32i_system));

	return isa;
}