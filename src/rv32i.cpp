#include "rv32i.hpp"
#include "utils.hpp"

ADD::ADD(uint32_t reg_a, uint32_t reg_b, uint32_t reg_dest)
	: reg_a(reg_a),
	  reg_b(reg_b),
	  reg_dest(reg_dest)
{
}

int32_t ADD::execute(CPUThread *thread)
{
	thread->get_regs()->regi[this->reg_dest] = 
		thread->get_regs()->regi[this->reg_a]
		+ thread->get_regs()->regi[this->reg_b];
	
	return 1;
}

SUB::SUB(uint32_t rs1, uint32_t rs2, uint32_t rsd)
	: rs1(rs1),
	  rs2(rs2),
	  rsd(rsd)
{
}

int32_t SUB::execute(CPUThread *thread)
{
	thread->get_regs()->regi[this->rsd] = 
		thread->get_regs()->regi[this->rs1]
		- thread->get_regs()->regi[this->rs2];
	
	return 1;
}
uint32_t ADD::to_instruction()
{
	uint32_t res = 0;

	res = set_bits(res, 0, 6, 0b0010011);
	res = set_bits(res, 7, 11, this->reg_dest);
	res = set_bits(res, 12, 14, 0b000);
	res = set_bits(res, 15, 19, this->reg_a);
	res = set_bits(res, 20, 24, this->reg_b);
	res = set_bits(res, 25, 31, 0b0000000);

	return res;
}

ADDI::ADDI(uint32_t reg_a, int32_t imm, uint32_t reg_dest)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest)
{
}

int32_t ADDI::execute(CPUThread *thread)
{
	thread->get_regs()->regi[this->reg_dest] = thread->get_regs()->regi[this->reg_a] + this->imm;

	return 1;
}

uint32_t ADDI::to_instruction()
{
	uint32_t res = 0;

	res = set_bits(res, 0, 6, 0b0010011);
	res = set_bits(res, 7, 11, this->reg_dest);
	res = set_bits(res, 12, 14, 0b000);
	res = set_bits(res, 15, 19, this->reg_a);
	res = set_bits(res, 20, 31, this->imm);

	return res;
}
SLLI::SLLI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest)
{
}

int32_t SLLI::execute(CPUThread *thread)
{
	thread->get_regs()->regi[this->reg_dest] = thread->get_regs()->regi[this->reg_a]
											   << this->imm;

	return 1;
}

SLTI::SLTI(uint32_t reg_a, int32_t imm, uint32_t reg_dest)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest)
{
}

int32_t SLTI::execute(CPUThread *thread)
{
	if (this->reg_a < this->imm)
	{
		thread->get_regs()->regi[this->reg_dest] = 1;
	}
	else
	{
		thread->get_regs()->regi[this->reg_dest] = 0;
	}

	return 1;
}

uint32_t SLTI::to_instruction()
{
	uint32_t res = 0;

	res = set_bits(res, 0, 6, 0b0010011);
	res = set_bits(res, 7, 11, this->reg_dest);
	res = set_bits(res, 12, 14, 0b010);
	res = set_bits(res, 15, 19, this->reg_a);
	res = set_bits(res, 20, 31, this->imm);

	return res;
}
SLTIU::SLTIU(uint32_t reg_a, uint32_t imm, uint32_t reg_dest)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest)
{
}

int32_t SLTIU::execute(CPUThread *thread)
{
	if ((uint32_t)this->reg_a < this->imm)
	{
		thread->get_regs()->regi[this->reg_dest] = 1;
	}
	else
	{
		thread->get_regs()->regi[this->reg_dest] = 0;
	}

	return 1;
}
SLTU::SLTU(uint32_t rs1, uint32_t rs2, uint32_t rsd)
	: rs1(rs1),
	  rs2(rs2),
	  rsd(rsd)
{
}

int32_t SLTU::execute(CPUThread *thread)
{
	uint32_t a = thread->get_regs()->regi[this->rs1];
	uint32_t b = thread->get_regs()->regi[this->rs2];
	if ((uint32_t)a < (uint32_t)b)
	{
		thread->get_regs()->regi[this->rsd] = 1;
	}
	else
	{
		thread->get_regs()->regi[this->rsd] = 0;
	}

	return 1;
}
SLT::SLT(uint32_t rs1, uint32_t rs2, uint32_t rsd)
	: rs1(rs1),
	  rs2(rs2),
	  rsd(rsd)
{
}

int32_t SLT::execute(CPUThread *thread)
{
	int32_t a = thread->get_regs()->regi[this->rs1];
	int32_t b = thread->get_regs()->regi[this->rs2];
	if (a < b)
	{
		thread->get_regs()->regi[this->rsd] = 1;
	}
	else
	{
		thread->get_regs()->regi[this->rsd] = 0;
	}

	return 1;
}
XORI::XORI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest)
{
}

int32_t XORI::execute(CPUThread *thread)
{
	thread->get_regs()->regi[this->reg_dest] = thread->get_regs()->regi[this->reg_a] ^ this->imm;

	return 1;
}

ANDI::ANDI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest)
{
}

int32_t ANDI::execute(CPUThread *thread)
{
	thread->get_regs()->regi[this->reg_dest] = thread->get_regs()->regi[this->reg_a] & this->imm;

	return 1;
}

SRLI::SRLI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest)
{
}

int32_t SRLI::execute(CPUThread *thread)
{
	thread->get_regs()->regi[this->reg_dest] = thread->get_regs()->regi[this->reg_a] >> this->imm;

	return 1;
}
SRA::SRA(uint32_t rs1, uint32_t rs2, uint32_t rsd)
	: rs1(rs1),
	  rs2(rs2),
	  rsd(rsd)
{
}

int32_t SRA::execute(CPUThread *thread)
{
	uint32_t shift = thread->get_regs()->regi[this->rs2];
	int32_t res = thread->get_regs()->regi[this->rs1] + shift;
	uint32_t sign_bit = res >> 31;

	res |= ((sign_bit << shift) - 1) << (32 - shift);

	thread->get_regs()->regi[this->rsd] = res;

	return 1;
}

SRAI::SRAI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest)
{
}

int32_t SRAI::execute(CPUThread *thread)
{
	int32_t res = thread->get_regs()->regi[this->reg_a] + this->imm;
	uint32_t sign_bit = res >> 31;

	res |= ((sign_bit << this->imm) - 1) << (32 - this->imm);

	thread->get_regs()->regi[this->reg_dest] = res;

	return 1;
}

ORI::ORI(uint32_t reg_a, uint32_t imm, uint32_t reg_dest)
	: reg_a(reg_a),
	  imm(imm),
	  reg_dest(reg_dest)
{
}

int32_t ORI::execute(CPUThread *thread)
{
	thread->get_regs()->regi[this->reg_dest] = thread->get_regs()->regi[this->reg_a] | this->imm;

	return 1;
}

XOR::XOR(uint32_t rs1, uint32_t rs2, uint32_t rsd) : rs1(rs1),
													 rs2(rs2),
													 rsd(rsd)
{
}

int32_t XOR::execute(CPUThread *thread)
{
	thread->get_regs()->regi[this->rsd] =
		thread->get_regs()->regi[this->rs1] ^ thread->get_regs()->regi[this->rs2];

	return 1;
}

OR::OR(uint32_t rs1, uint32_t rs2, uint32_t rsd) : rs1(rs1),
												   rs2(rs2),
												   rsd(rsd)
{
}

int32_t OR::execute(CPUThread *thread)
{
	thread->get_regs()->regi[this->rsd] =
		thread->get_regs()->regi[this->rs1] | thread->get_regs()->regi[this->rs2];

	return 1;
}

AND::AND(uint32_t rs1, uint32_t rs2, uint32_t rsd) : rs1(rs1),
													 rs2(rs2),
													 rsd(rsd)
{
}

int32_t AND::execute(CPUThread *thread)
{
	thread->get_regs()->regi[this->rsd] =
		thread->get_regs()->regi[this->rs1] & thread->get_regs()->regi[this->rs2];

	return 1;
}

SRL::SRL(uint32_t rs1, uint32_t rs2, uint32_t rsd) : rs1(rs1),
													 rs2(rs2),
													 rsd(rsd)
{
}

int32_t SRL::execute(CPUThread *thread)
{
	thread->get_regs()->regi[this->rsd] =
		thread->get_regs()->regi[this->rs1] >> thread->get_regs()->regi[this->rs2];

	return 1;
}
SLL::SLL(uint32_t rs1, uint32_t rs2, uint32_t rsd) : rs1(rs1),
													 rs2(rs2),
													 rsd(rsd)
{
}

int32_t SLL::execute(CPUThread *thread)
{
	thread->get_regs()->regi[this->rsd] =
		thread->get_regs()->regi[this->rs1] << thread->get_regs()->regi[this->rs2];

	return 1;
}

LUI::LUI(uint32_t imm, uint32_t rsd) : imm(imm), rsd(rsd) {}

int32_t LUI::execute(CPUThread* thread) {
	thread->get_regs()->regi[this->rsd] = imm;

	return 1;
}

AUIPC::AUIPC(int32_t imm, uint32_t rsd) : imm(imm), rsd(rsd) {}

int32_t AUIPC::execute(CPUThread* thread) {
	thread->get_regs()->regi[this->rsd] = thread->get_regs()->pc + this->imm;

	return 1;
}


BEQ::BEQ(uint32_t rs1, uint32_t rs2, int32_t imm) : rs1(rs1), rs2(rs2), imm(imm)
{}

int32_t BEQ::execute(CPUThread* thread) {
	if(thread->get_regs()->regi[this->rs1] == thread->get_regs()->regi[this->rs2]) {
		return this->imm;
	}

	return 1;
}

BNE::BNE(uint32_t rs1, uint32_t rs2, int32_t imm) : rs1(rs1), rs2(rs2), imm(imm)
{}

int32_t BNE::execute(CPUThread* thread) {
	if(thread->get_regs()->regi[this->rs1] != thread->get_regs()->regi[this->rs2]) {
		return this->imm;
	}

	return 1;
}

BLT::BLT(uint32_t rs1, uint32_t rs2, int32_t imm) : rs1(rs1), rs2(rs2), imm(imm)
{}

int32_t BLT::execute(CPUThread* thread) {
	if(thread->get_regs()->regi[this->rs1] < thread->get_regs()->regi[this->rs2]) {
		return this->imm;
	}

	return 1;
}

BGT::BGT(uint32_t rs1, uint32_t rs2, int32_t imm) : rs1(rs1), rs2(rs2), imm(imm)
{}

int32_t BGT::execute(CPUThread* thread) {
	if(thread->get_regs()->regi[this->rs1] > thread->get_regs()->regi[this->rs2]) {
		return this->imm;
	}

	return 1;
}
BGE::BGE(uint32_t rs1, uint32_t rs2, int32_t imm) : rs1(rs1), rs2(rs2), imm(imm)
{}

int32_t BGE::execute(CPUThread* thread) {
	if(thread->get_regs()->regi[this->rs1] >= thread->get_regs()->regi[this->rs2]) {
		return this->imm;
	}

	return 1;
}
BLE::BLE(uint32_t rs1, uint32_t rs2, int32_t imm) : rs1(rs1), rs2(rs2), imm(imm)
{}

int32_t BLE::execute(CPUThread* thread) {
	if(thread->get_regs()->regi[this->rs1] <= thread->get_regs()->regi[this->rs2]) {
		return this->imm;
	}

	return 1;
}
BLTU::BLTU(uint32_t rs1, uint32_t rs2, uint32_t imm) : rs1(rs1), rs2(rs2), imm(imm)
{}

int32_t BLTU::execute(CPUThread* thread) {
	if(thread->get_regs()->regi[this->rs1] < thread->get_regs()->regi[this->rs2]) {
		return this->imm;
	}

	return 1;
}

BGEU::BGEU(uint32_t rs1, uint32_t rs2, uint32_t imm) : rs1(rs1), rs2(rs2), imm(imm)
{}
int32_t BGEU::execute(CPUThread* thread) {
	if(thread->get_regs()->regi[this->rs1] >= thread->get_regs()->regi[this->rs2]) {
		return this->imm;
	}

	return 1;
}

LOAD::LOAD(uint32_t base, LoadType type, uint32_t dest, int32_t offset)
	:base(base),
	type(type),
	dest(dest),
	offset(offset)
{}

int32_t LOAD::execute(CPUThread* thread) {
	uint32_t read_addr = (uint32_t)(thread->get_regs()->regi[this->base]
		+ this->offset);
	
	uint32_t read_val = thread->get_ram()->get(read_addr);

	int32_t store_val = 0;
	switch(this->type){
		case LoadType::LB:
			store_val = set_bits(
				store_val,
				0, 7,
				thread->get_ram()->get(read_val + 0)
			);
			
			store_val = sext(store_val, 7);

			break;
		case LoadType::LBU:
			store_val = set_bits(
				store_val,
				0, 7,
				thread->get_ram()->get(read_val + 0)
			);
			break;
		case LoadType::LH:
			store_val = set_bits(
				store_val,
				0, 7,
				thread->get_ram()->get(read_val + 0)
			);
			store_val = set_bits(
				store_val,
				8, 15,
				thread->get_ram()->get(read_val + 1)
			);

			store_val = sext(store_val, 15);
			break;
		case LoadType::LHU:
			store_val = set_bits(
				store_val,
				0, 7,
				thread->get_ram()->get(read_val + 0)
			);
			store_val = set_bits(
				store_val,
				8, 15,
				thread->get_ram()->get(read_val + 1)
			);
			break;
		case LoadType::LW:
			store_val = set_bits(
				store_val,
				0, 7,
				thread->get_ram()->get(read_val + 0)
			);
			store_val = set_bits(
				store_val,
				8, 15,
				thread->get_ram()->get(read_val + 1)
			);
			store_val = set_bits(
				store_val,
				16, 23,
				thread->get_ram()->get(read_val + 2)
			);
			store_val = set_bits(
				store_val,
				24, 31,
				thread->get_ram()->get(read_val + 3)
			);
			break;
	}

	thread->get_regs()->regi[this->dest] = store_val;

	return 1;
}

STORE::STORE(uint32_t src, uint32_t base, StoreType type, int32_t offset)
	: src(src),
	base(base),
	type(type),
	offset(offset)
{}

int32_t STORE::execute(CPUThread* thread){
	uint32_t reg_val = thread->get_regs()->regi[this->src];

	uint32_t write_addr = (uint32_t)(thread->get_regs()->regi[this->base]
		+ this->offset);
	
	switch(this->type){
		case StoreType::SB:
			thread->get_ram()->set(write_addr + 0, bits(reg_val, 0, 7));
			break;
		case StoreType::SH:
			thread->get_ram()->set(write_addr + 0, bits(reg_val, 0, 7));
			thread->get_ram()->set(write_addr + 1, bits(reg_val, 8, 15));
			break;
		case StoreType::SW:
			thread->get_ram()->set(write_addr + 0, bits(reg_val, 0, 7));
			thread->get_ram()->set(write_addr + 1, bits(reg_val, 8, 15));
			thread->get_ram()->set(write_addr + 2, bits(reg_val, 16, 23));
			thread->get_ram()->set(write_addr + 3, bits(reg_val, 24, 31));
			break;
	}

	return 1;
}

int32_t FENCE::execute(CPUThread* thread){
	std::cout << "Fence? Don't ask me" << std::endl;
	return 1;
}

int32_t ECALL::execute(CPUThread* thread) {
	std::cout << "ECALL" << std::endl;
	return 1;
}

int32_t EBREAK::execute(CPUThread* thread) {
	std::cout << "EBREAK" << std::endl;
	return 1;
}

std::unique_ptr<AInstruction> rv32i_op_imm(uint32_t instr)
{
	uint32_t rd = bits(instr, 7, 11);
	uint32_t funct3 = bits(instr, 12, 14);
	uint32_t rs1 = bits(instr, 15, 19);
	int32_t imm_s = extract_imm_signed(instr, ImmType::I);
	uint32_t imm_u = extract_imm_unsigned(instr, ImmType::I);

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
			return std::make_unique<UndefInstr>(instr);
		}
	case 6:
		return std::make_unique<ORI>(rs1, imm_u, rd);
	case 7:
		return std::make_unique<ANDI>(rs1, imm_u, rd);
	default:
		return std::make_unique<UndefInstr>(instr);
	}

	return std::make_unique<UndefInstr>(instr);
}

std::unique_ptr<AInstruction> rv32i_op(uint32_t instr)
{
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
			return std::make_unique<UndefInstr>(instr);
		}
	case 0x20:
		switch (f3)
		{
		case 0:
			return std::make_unique<SUB>(rs1, rs2, rd);
		case 5:
			return std::make_unique<SRA>(rs1, rs2, rd);
		default:
			return std::make_unique<UndefInstr>(instr);
		}
	default:
		return std::make_unique<UndefInstr>(instr);
	}
}

std::unique_ptr<AInstruction> rv32i_lui(uint32_t instr)
{
	return std::make_unique<LUI>(
		bits(instr, 21, 31),
		bits(instr, 7, 11));
}

std::unique_ptr<AInstruction> rv32i_auipc(uint32_t instr)
{
	return std::make_unique<AUIPC>(
		bits(instr, 21, 31),
		bits(instr, 7, 11));
}

std::unique_ptr<AInstruction> rv32i_jal(uint32_t instr)
{
	return std::make_unique<AUIPC>(
		bits(instr, 21, 31),
		bits(instr, 7, 11));
}

std::unique_ptr<AInstruction> rv32i_jalr(uint32_t instr)
{
	return std::make_unique<AUIPC>(
		bits(instr, 21, 31),
		bits(instr, 7, 11));
}

std::unique_ptr<AInstruction> rv32i_branch(uint32_t instr)
{
	uint32_t f3 = bits(instr, 12, 14);
	uint32_t rs1 = bits(instr, 15, 19);
	uint32_t rs2 = bits(instr, 20, 24);
	int32_t imm_s = extract_imm_signed(instr, ImmType::B);
	uint32_t imm_u = extract_imm_unsigned(instr, ImmType::B);

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
		return std::make_unique<UndefInstr>(instr);
	}
}

std::unique_ptr<AInstruction> rv32i_load(uint32_t instr)
{
	LoadType type;
	switch(bits(instr, 12, 14)){
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
			return std::make_unique<UndefInstr>(instr);
	}

	return std::make_unique<LOAD>(
		bits(instr, 15, 19), 	// rs1
		type,
		bits(instr, 7, 11), 	// rd
		extract_imm_signed(instr, ImmType::I)
	);
}
std::unique_ptr<AInstruction> rv32i_store(uint32_t instr)
{
	StoreType type;
	switch(bits(instr, 12, 14)) {
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
			return std::make_unique<UndefInstr>(instr);
	}

	return std::make_unique<STORE>(
		bits(instr, 20, 24),	// rs2 (src)
		bits(instr, 15, 19), 	// rs1 (base)
		type,
		extract_imm_signed(instr, ImmType::S)
	);
}

std::unique_ptr<AInstruction> rv32i_misc_mem(uint32_t instr)
{
	return std::make_unique<FENCE>();
}

std::unique_ptr<AInstruction> rv32i_system(uint32_t instr)
{
	uint32_t non_op = bits(instr, 7, 31);

	if (non_op == 0x0)
	{
		return std::make_unique<ECALL>();
	}
	else if (non_op == 0x2000)
	{
		return std::make_unique<EBREAK>();
	}

	return std::make_unique<UndefInstr>(instr);
}
std::unique_ptr<ISA> isa_rv32i()
{
	std::unique_ptr<ISA> isa = std::make_unique<ISA>();

	isa.get()->add_instr(0b0001111, instr_gen(rv32i_misc_mem));
	isa.get()->add_instr(0b0010011, instr_gen(rv32i_op_imm));
	isa.get()->add_instr(0b0010111, instr_gen(rv32i_auipc));
	isa.get()->add_instr(0b0110011, instr_gen(rv32i_op));
	isa.get()->add_instr(0b0110111, instr_gen(rv32i_lui));
	isa.get()->add_instr(0b1101111, instr_gen(rv32i_jal));
	isa.get()->add_instr(0b1100011, instr_gen(rv32i_branch));
	isa.get()->add_instr(0b1100111, instr_gen(rv32i_jalr));
	isa.get()->add_instr(0b1110011, instr_gen(rv32i_system));

	return isa;
}