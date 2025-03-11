#pragma once

#include <functional>
#include <cstdint>

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

// Not really a hashmap, as I want the key to be the opcode (which is an
// unsigned int). When we register the ISA we'll check that there are no
// duplicate keys.
using ISA = std::vector<std::pair<uint32_t, std::function<AInstruction (uint32_t)>>>;

// Create the RV32i ISA
ISA isa_rv32i();

// The InstructionParser stores instruction sets. Can be loaded with 
// multiple modules of instructions.
class InstructionParser{
public:
	void register_isa(ISA* isa);
	AInstruction* parse(uint32_t instruction);
private:
	ISA isa;
};
