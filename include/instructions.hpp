#pragma once

#include <functional>
#include <cstdint>
#include <memory>
#include <map>

class CPUThread;

// All instructions will implement AInstruction
// 
// Honestly, I'd love to use Rust's enums here, as we can define both the
// full sets of instructions as an enum, and also the data attached to each
// of them. Instead, I'll use abstract classes, where implementations can
// store the necessary data for each command.
class AInstruction{
	public:
		// Probably the most important method in the whole application
		//
		// executes an instruction on the given CPU (might change this
		// to take CPUCore/CPUThread as input instead). Return the 
		// _offset_ to be applied to the program pointer;
		virtual int32_t execute(CPUThread* thread) = 0;
};

class UndefInstr : public AInstruction{
	public:
		UndefInstr(uint32_t instr);
		int32_t execute(CPUThread* thread);
	private:
		uint32_t instr;
};

class ADD : public AInstruction{
	public:
		ADD(uint32_t reg_a, uint32_t reg_b, uint32_t reg_dest);
		int32_t execute(CPUThread* thread);
	private:
		uint32_t reg_a;
		uint32_t reg_b;
		uint32_t reg_dest;
};


class ADDI : public AInstruction{
	public:
		ADDI(uint32_t reg_a, int32_t imm, uint32_t reg_dest);
		int32_t execute(CPUThread* thread);
	private:
		uint32_t reg_a;
		int32_t imm;
		uint32_t reg_dest;
};

class SLLI : public AInstruction{
	public:
		SLLI(uint32_t reg_a, int32_t imm, uint32_t reg_dest);
		int32_t execute(CPUThread* thread);
	private:
		uint32_t reg_a;
		int32_t imm;
		uint32_t reg_dest;
};

class SLTI : public AInstruction{
	public:
		SLTI(uint32_t reg_a, int32_t imm, uint32_t reg_dest);
		int32_t execute(CPUThread* thread);
	private:
		uint32_t reg_a;
		int32_t imm;
		uint32_t reg_dest;
};

class SLTIU : public AInstruction{
	public:
		SLTIU(uint32_t reg_a, int32_t imm, uint32_t reg_dest);
		int32_t execute(CPUThread* thread);
	private:
		uint32_t reg_a;
		int32_t imm;
		uint32_t reg_dest;
};

class XORI : public AInstruction{
	public:
		XORI(uint32_t reg_a, int32_t imm, uint32_t reg_dest);
		int32_t execute(CPUThread* thread);
	private:
		uint32_t reg_a;
		int32_t imm;
		uint32_t reg_dest;
};

class ANDI : public AInstruction{
	public:
		ANDI(uint32_t reg_a, int32_t imm, uint32_t reg_dest);
		int32_t execute(CPUThread* thread);
	private:
		uint32_t reg_a;
		int32_t imm;
		uint32_t reg_dest;
};

class SRLI : public AInstruction{
	public:
		SRLI(uint32_t reg_a, int32_t imm, uint32_t reg_dest);
		int32_t execute(CPUThread* thread);
	private:
		uint32_t reg_a;
		int32_t imm;
		uint32_t reg_dest;
};

class SRAI : public AInstruction{
	public:
		SRAI(uint32_t reg_a, int32_t imm, uint32_t reg_dest);
		int32_t execute(CPUThread* thread);
	private:
		uint32_t reg_a;
		int32_t imm;
		uint32_t reg_dest;
};

class ORI : public AInstruction{
	public:
		ORI(uint32_t reg_a, int32_t imm, uint32_t reg_dest);
		int32_t execute(CPUThread* thread);
	private:
		uint32_t reg_a;
		int32_t imm;
		uint32_t reg_dest;
};

using instr_gen = std::function<std::unique_ptr<AInstruction>(uint32_t)>;

// Instruction Set Assembly
class ISA{
	public:
		// add_instr
		// 
		// Adds instructions to the ISA
		//
		// return bool is the result of trying to add the instruction
		bool add_instr(uint32_t opcode, instr_gen f);
		
		std::map<uint32_t, instr_gen>* get_map(){
			return &this->instrs;
		}

	private:
		std::map<uint32_t, instr_gen> instrs;
};

// Create the RV32i ISA
std::unique_ptr<ISA> isa_rv32i();

// The InstructionParser stores instruction sets. Can be loaded with 
// multiple modules of instructions.
class InstructionParser{
public:
	void register_isa(std::unique_ptr<ISA> isa);
	std::unique_ptr<AInstruction> parse(uint32_t instruction);
private:
	std::map<uint32_t, instr_gen> instrs;
};
