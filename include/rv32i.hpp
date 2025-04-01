#pragma once

#include "cpu.hpp"
#include "instructions.hpp"

#include <string>

class ADD : public AInstruction
{
public:
	ADD(uint32_t reg_a, uint32_t reg_b, uint32_t reg_dest);
	ADD(uint32_t reg_a, uint32_t reg_b, uint32_t reg_dest, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	uint32_t to_instruction() override;
	std::string to_string() override;

private:
	uint32_t reg_a;
	uint32_t reg_b;
	uint32_t reg_dest;
	uint8_t instr_bytes;
};

class ADDI : public AInstruction
{
public:
	ADDI(uint32_t reg_a, int32_t imm, uint32_t reg_dest);
	ADDI(uint32_t reg_a, int32_t imm, uint32_t reg_dest, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	uint32_t to_instruction() override;
	std::string to_string() override;

private:
	uint32_t reg_a;
	int32_t imm;
	uint32_t reg_dest;
	uint8_t instr_bytes;
};

class SLLI : public AInstruction
{
public:
	SLLI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest);
	SLLI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t reg_a;
	uint32_t imm;
	uint32_t reg_dest;
	uint8_t instr_bytes;
};

class SLTI : public AInstruction
{
public:
	SLTI(uint32_t reg_a, int32_t imm, uint32_t reg_dest);
	SLTI(uint32_t reg_a, int32_t imm, uint32_t reg_dest, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	uint32_t to_instruction() override;
	std::string to_string() override;

private:
	uint32_t reg_a;
	int32_t imm;
	uint32_t reg_dest;
	uint8_t instr_bytes;
};

class SLTIU : public AInstruction
{
public:
	SLTIU(uint32_t reg_a, uint32_t imm, uint32_t reg_dest);
	SLTIU(uint32_t reg_a, uint32_t imm, uint32_t reg_dest, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t reg_a;
	uint32_t imm;
	uint32_t reg_dest;
	uint8_t instr_bytes;
};

class XORI : public AInstruction
{
public:
	XORI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest);
	XORI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t reg_a;
	uint32_t imm;
	uint32_t reg_dest;
	uint8_t instr_bytes;
};

class ANDI : public AInstruction
{
public:
	ANDI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest);
	ANDI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t reg_a;
	uint32_t imm;
	uint32_t reg_dest;
	uint8_t instr_bytes;
};

class SRLI : public AInstruction
{
public:
	SRLI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest);
	SRLI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t reg_a;
	uint32_t imm;
	uint32_t reg_dest;
	uint8_t instr_bytes;
};

class SRAI : public AInstruction
{
public:
	SRAI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest);
	SRAI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t reg_a;
	uint32_t imm;
	uint32_t reg_dest;
	uint8_t instr_bytes;
};

class ORI : public AInstruction
{
public:
	ORI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest);
	ORI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t reg_a;
	uint32_t imm;
	uint32_t reg_dest;
	uint8_t instr_bytes;
};

class SLL : public AInstruction
{
public:
	SLL(uint32_t rs1, uint32_t rs2, uint32_t rsd);
	SLL(uint32_t rs1, uint32_t rs2, uint32_t rsd, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t rs1;
	uint32_t rs2;
	uint32_t rsd;
	uint8_t instr_bytes;
};

class SLT : public AInstruction
{
public:
	SLT(uint32_t rs1, uint32_t rs2, uint32_t rsd);
	SLT(uint32_t rs1, uint32_t rs2, uint32_t rsd, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t rs1;
	uint32_t rs2;
	uint32_t rsd;
	uint8_t instr_bytes;
};

class SLTU : public AInstruction
{
public:
	SLTU(uint32_t rs1, uint32_t rs2, uint32_t rsd);
	SLTU(uint32_t rs1, uint32_t rs2, uint32_t rsd, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t rs1;
	uint32_t rs2;
	uint32_t rsd;
	uint8_t instr_bytes;
};

class XOR : public AInstruction
{
public:
	XOR(uint32_t rs1, uint32_t rs2, uint32_t rsd);
	XOR(uint32_t rs1, uint32_t rs2, uint32_t rsd, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t rs1;
	uint32_t rs2;
	uint32_t rsd;
	uint8_t instr_bytes;
};

class SRL : public AInstruction
{
public:
	SRL(uint32_t rs1, uint32_t rs2, uint32_t rsd);
	SRL(uint32_t rs1, uint32_t rs2, uint32_t rsd, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t rs1;
	uint32_t rs2;
	uint32_t rsd;
	uint8_t instr_bytes;
};

class OR : public AInstruction
{
public:
	OR(uint32_t rs1, uint32_t rs2, uint32_t rsd);
	OR(uint32_t rs1, uint32_t rs2, uint32_t rsd, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t rs1;
	uint32_t rs2;
	uint32_t rsd;
	uint8_t instr_bytes;
};

class AND : public AInstruction
{
public:
	AND(uint32_t rs1, uint32_t rs2, uint32_t rsd);
	AND(uint32_t rs1, uint32_t rs2, uint32_t rsd, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t rs1;
	uint32_t rs2;
	uint32_t rsd;
	uint8_t instr_bytes;
};

class SUB : public AInstruction
{
public:
	SUB(uint32_t rs1, uint32_t rs2, uint32_t rsd);
	SUB(uint32_t rs1, uint32_t rs2, uint32_t rsd, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t rs1;
	uint32_t rs2;
	uint32_t rsd;
	uint8_t instr_bytes;
};

class SRA : public AInstruction
{
public:
	SRA(uint32_t rs1, uint32_t rs2, uint32_t rsd);
	SRA(uint32_t rs1, uint32_t rs2, uint32_t rsd, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t rs1;
	uint32_t rs2;
	uint32_t rsd;
	uint8_t instr_bytes;
};

class LUI : public AInstruction
{
public:
	LUI(uint32_t imm, uint32_t rsd);
	LUI(uint32_t imm, uint32_t rsd, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t imm;
	uint32_t rsd;
	uint8_t instr_bytes;
};

class AUIPC : public AInstruction
{
public:
	AUIPC(int32_t imm, uint32_t rsd);
	AUIPC(int32_t imm, uint32_t rsd, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	int32_t imm;
	uint32_t rsd;
	uint8_t instr_bytes;
};

class BEQ : public AInstruction
{
public:
	BEQ(uint32_t rs1, uint32_t rs2, int32_t imm);
	BEQ(uint32_t rs1, uint32_t rs2, int32_t imm, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t rs1;
	uint32_t rs2;
	int32_t imm;
	uint8_t instr_bytes;
};

class BNE : public AInstruction
{
public:
	BNE(uint32_t rs1, uint32_t rs2, int32_t imm);
	BNE(uint32_t rs1, uint32_t rs2, int32_t imm, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t rs1;
	uint32_t rs2;
	int32_t imm;
	uint8_t instr_bytes;
};

class BLT : public AInstruction
{
public:
	BLT(uint32_t rs1, uint32_t rs2, int32_t imm);
	BLT(uint32_t rs1, uint32_t rs2, int32_t imm, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t rs1;
	uint32_t rs2;
	int32_t imm;
	uint8_t instr_bytes;
};
class BGT : public AInstruction
{
public:
	BGT(uint32_t rs1, uint32_t rs2, int32_t imm);
	BGT(uint32_t rs1, uint32_t rs2, int32_t imm, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t rs1;
	uint32_t rs2;
	int32_t imm;
	uint8_t instr_bytes;
};
class BGE : public AInstruction
{
public:
	BGE(uint32_t rs1, uint32_t rs2, int32_t imm);
	BGE(uint32_t rs1, uint32_t rs2, int32_t imm, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t rs1;
	uint32_t rs2;
	int32_t imm;
	uint8_t instr_bytes;
};
class BLE : public AInstruction
{
public:
	BLE(uint32_t rs1, uint32_t rs2, int32_t imm);
	BLE(uint32_t rs1, uint32_t rs2, int32_t imm, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t rs1;
	uint32_t rs2;
	int32_t imm;
	uint8_t instr_bytes;
};
class BLTU : public AInstruction
{
public:
	BLTU(uint32_t rs1, uint32_t rs2, uint32_t imm);
	BLTU(uint32_t rs1, uint32_t rs2, uint32_t imm, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t rs1;
	uint32_t rs2;
	uint32_t imm;
	uint8_t instr_bytes;
};

class BGEU : public AInstruction
{
public:
	BGEU(uint32_t rs1, uint32_t rs2, uint32_t imm);
	BGEU(uint32_t rs1, uint32_t rs2, uint32_t imm, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t rs1;
	uint32_t rs2;
	uint32_t imm;
	uint8_t instr_bytes;
};

class JAL : public AInstruction{
	public:
		JAL(uint32_t rd, int32_t imm);
		JAL(uint32_t rd, int32_t imm, int32_t instr_bytes);
		InstrResult execute(CPUThread* thread) override;
	std::string to_string() override;
	private:
        uint32_t rd;
		int32_t imm;
		int32_t instr_bytes;
};

class JALR : public AInstruction{
	public:
		JALR(uint32_t rs1, uint32_t rd, int32_t imm);
		JALR(uint32_t rs1, uint32_t rd, int32_t imm, uint8_t instr_bytes);
		InstrResult execute(CPUThread* thread) override;
	std::string to_string() override;
	private:
		uint32_t rs1;
        uint32_t rd;
		int32_t imm;
		uint8_t instr_bytes;
};

enum LoadType {
	LB,
	LH,
	LW,
	LBU,
	LHU
};

class LOAD : public AInstruction
{
public:
	LOAD(uint32_t base, LoadType type, uint32_t dest, int32_t offset);
	LOAD(uint32_t base, LoadType type, uint32_t dest, int32_t offset, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t base;
	LoadType type;
	uint32_t dest;
	int32_t offset;
	uint8_t instr_bytes;
};

enum StoreType {
	SB,
	SH,
	SW
};

class STORE : public AInstruction
{
public:
	STORE(uint32_t src, uint32_t base, StoreType type, int32_t offset);
	STORE(uint32_t src, uint32_t base, StoreType type, int32_t offset, uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;

private:
	uint32_t src;
	uint32_t base;
	StoreType type;
	int32_t offset;
	uint8_t instr_bytes;
};

class FENCE : public AInstruction
{
public:
	FENCE();
	FENCE(uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;
private:
	uint8_t instr_bytes;
};

class ECALL : public AInstruction
{
public:
	ECALL();
	ECALL(uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;
private:
	uint8_t instr_bytes;
};

class EBREAK : public AInstruction
{
public:
	EBREAK();
	EBREAK(uint8_t instr_bytes);
	InstrResult execute(CPUThread *thread) override;
	std::string to_string() override;
private:
	uint8_t instr_bytes;
};
// Create the RV32i ISA
std::unique_ptr<ISA> isa_rv32i();
