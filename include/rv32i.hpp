#pragma once

#include "cpu.hpp"
#include "instructions.hpp"

class ADD : public AInstruction
{
public:
	ADD(uint32_t reg_a, uint32_t reg_b, uint32_t reg_dest);
	int32_t execute(CPUThread *thread) override;
	uint32_t to_instruction() override;

private:
	uint32_t reg_a;
	uint32_t reg_b;
	uint32_t reg_dest;
};

class ADDI : public AInstruction
{
public:
	ADDI(uint32_t reg_a, int32_t imm, uint32_t reg_dest);
	int32_t execute(CPUThread *thread) override;
	uint32_t to_instruction() override;

private:
	uint32_t reg_a;
	int32_t imm;
	uint32_t reg_dest;
};

class SLLI : public AInstruction
{
public:
	SLLI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t reg_a;
	uint32_t imm;
	uint32_t reg_dest;
};

class SLTI : public AInstruction
{
public:
	SLTI(uint32_t reg_a, int32_t imm, uint32_t reg_dest);
	int32_t execute(CPUThread *thread) override;
	uint32_t to_instruction() override;

private:
	uint32_t reg_a;
	int32_t imm;
	uint32_t reg_dest;
};

class SLTIU : public AInstruction
{
public:
	SLTIU(uint32_t reg_a, uint32_t imm, uint32_t reg_dest);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t reg_a;
	uint32_t imm;
	uint32_t reg_dest;
};

class XORI : public AInstruction
{
public:
	XORI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t reg_a;
	uint32_t imm;
	uint32_t reg_dest;
};

class ANDI : public AInstruction
{
public:
	ANDI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t reg_a;
	uint32_t imm;
	uint32_t reg_dest;
};

class SRLI : public AInstruction
{
public:
	SRLI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t reg_a;
	uint32_t imm;
	uint32_t reg_dest;
};

class SRAI : public AInstruction
{
public:
	SRAI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t reg_a;
	uint32_t imm;
	uint32_t reg_dest;
};

class ORI : public AInstruction
{
public:
	ORI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t reg_a;
	uint32_t imm;
	uint32_t reg_dest;
};

class SLL : public AInstruction
{
public:
	SLL(uint32_t rs1, uint32_t rs2, uint32_t rsd);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t rs1;
	uint32_t rs2;
	uint32_t rsd;
};

class SLT : public AInstruction
{
public:
	SLT(uint32_t rs1, uint32_t rs2, uint32_t rsd);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t rs1;
	uint32_t rs2;
	uint32_t rsd;
};

class SLTU : public AInstruction
{
public:
	SLTU(uint32_t rs1, uint32_t rs2, uint32_t rsd);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t rs1;
	uint32_t rs2;
	uint32_t rsd;
};

class XOR : public AInstruction
{
public:
	XOR(uint32_t rs1, uint32_t rs2, uint32_t rsd);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t rs1;
	uint32_t rs2;
	uint32_t rsd;
};

class SRL : public AInstruction
{
public:
	SRL(uint32_t rs1, uint32_t rs2, uint32_t rsd);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t rs1;
	uint32_t rs2;
	uint32_t rsd;
};

class OR : public AInstruction
{
public:
	OR(uint32_t rs1, uint32_t rs2, uint32_t rsd);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t rs1;
	uint32_t rs2;
	uint32_t rsd;
};

class AND : public AInstruction
{
public:
	AND(uint32_t rs1, uint32_t rs2, uint32_t rsd);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t rs1;
	uint32_t rs2;
	uint32_t rsd;
};

class SUB : public AInstruction
{
public:
	SUB(uint32_t rs1, uint32_t rs2, uint32_t rsd);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t rs1;
	uint32_t rs2;
	uint32_t rsd;
};

class SRA : public AInstruction
{
public:
	SRA(uint32_t rs1, uint32_t rs2, uint32_t rsd);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t rs1;
	uint32_t rs2;
	uint32_t rsd;
};

class LUI : public AInstruction
{
public:
	LUI(uint32_t imm, uint32_t rsd);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t imm;
	uint32_t rsd;
};

class AUIPC : public AInstruction
{
public:
	AUIPC(int32_t imm, uint32_t rsd);
	int32_t execute(CPUThread *thread) override;

private:
	int32_t imm;
	uint32_t rsd;
};

class BEQ : public AInstruction
{
public:
	BEQ(uint32_t rs1, uint32_t rs2, int32_t imm);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t rs1;
	uint32_t rs2;
	int32_t imm;
};

class BNE : public AInstruction
{
public:
	BNE(uint32_t rs1, uint32_t rs2, int32_t imm);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t rs1;
	uint32_t rs2;
	int32_t imm;
};

class BLT : public AInstruction
{
public:
	BLT(uint32_t rs1, uint32_t rs2, int32_t imm);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t rs1;
	uint32_t rs2;
	int32_t imm;
};
class BGT : public AInstruction
{
public:
	BGT(uint32_t rs1, uint32_t rs2, int32_t imm);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t rs1;
	uint32_t rs2;
	int32_t imm;
};
class BGE : public AInstruction
{
public:
	BGE(uint32_t rs1, uint32_t rs2, int32_t imm);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t rs1;
	uint32_t rs2;
	int32_t imm;
};
class BLE : public AInstruction
{
public:
	BLE(uint32_t rs1, uint32_t rs2, int32_t imm);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t rs1;
	uint32_t rs2;
	int32_t imm;
};
class BLTU : public AInstruction
{
public:
	BLTU(uint32_t rs1, uint32_t rs2, uint32_t imm);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t rs1;
	uint32_t rs2;
	uint32_t imm;
};

class BGEU : public AInstruction
{
public:
	BGEU(uint32_t rs1, uint32_t rs2, uint32_t imm);
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t rs1;
	uint32_t rs2;
	uint32_t imm;
};

class JAL : public AInstruction{
	public:
		JAL(uint32_t rd, int32_t imm);
		int32_t execute(CPUThread* thread);
	private:
        uint32_t rd;
		int32_t imm;
};

class JALR : public AInstruction{
	public:
		JALR(uint32_t rs1, uint32_t rd, int32_t imm);
		int32_t execute(CPUThread* thread);
	private:
		uint32_t rs1;
        uint32_t rd;
		int32_t imm;
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
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t base;
	LoadType type;
	uint32_t dest;
	int32_t offset;
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
	int32_t execute(CPUThread *thread) override;

private:
	uint32_t src;
	uint32_t base;
	StoreType type;
	uint32_t offset;
};

class FENCE : public AInstruction
{
public:
	int32_t execute(CPUThread *thread) override;
};

class ECALL : public AInstruction
{
public:
	int32_t execute(CPUThread *thread) override;
};

class EBREAK : public AInstruction
{
public:
	int32_t execute(CPUThread *thread) override;
};
// Create the RV32i ISA
std::unique_ptr<ISA> isa_rv32i();
