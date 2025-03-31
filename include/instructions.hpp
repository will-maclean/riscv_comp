#pragma once

#include <functional>
#include <cstdint>
#include <memory>
#include <map>
#include <iostream>
#include <string>

class CPUThread;

enum ExeFlow{
	CONTINUE,
	STOP,
	ERROR,
};

struct InstrResult{
	int32_t pc_offset;
	ExeFlow flow;

	InstrResult(uint32_t pc_offset, ExeFlow flow) : pc_offset(pc_offset), flow(flow) {}
	explicit InstrResult(uint32_t pc_offset) : pc_offset(pc_offset), flow(ExeFlow::CONTINUE) {}
};

// All instructions will implement AInstruction
// 
// Honestly, I'd love to use Rust's enums here, as we can define both the
// full sets of instructions as an enum, and also the data attached to each
// of them. Instead, I'll use abstract classes, where implementations can
// store the necessary data for each command.
class AInstruction{
	public:
		virtual ~AInstruction() = default;

		// Probably the most important method in the whole application
		//
		// executes an instruction on the given CPU (might change this
		// to take CPUCore/CPUThread as input instead). Return the 
		// _offset_ to be applied to the program pointer;
		virtual InstrResult execute(CPUThread* thread) = 0;

		// Converts an instruction to a 32-bit code
		// Not necessary to implement but useful
		virtual uint32_t to_instruction(){
			std::cout << "No to_instruction() defined" << std::endl;
			return 0;
		}

		virtual std::string to_string() = 0;
};

class UndefInstr : public AInstruction{
	public:
		UndefInstr(uint32_t instr);
		InstrResult execute(CPUThread* thread);
		std::string to_string();
	private:
		uint32_t instr;
};

const uint32_t POSITIVE_BIT = 0;

enum ImmType {
	R,
	I,
	S,
	B,
	U,
	J
};

int32_t extract_imm_signed(uint32_t instr, ImmType imm_type);
uint32_t extract_imm_unsigned(uint32_t instr, ImmType imm_type);

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

// The InstructionParser stores instruction sets. Can be loaded with 
// multiple modules of instructions.
class InstructionParser{
public:
	void register_isa(std::unique_ptr<ISA> isa);
	std::unique_ptr<AInstruction> parse(uint32_t instruction);
private:
	std::map<uint32_t, instr_gen> instrs;
};
