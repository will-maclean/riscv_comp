#include <gtest/gtest.h>
#include <comp.hpp>
#include <rv32i.hpp>
#include "utils.hpp"
#include "cpu.hpp"
#include "instructions.hpp"

class MockCPUThread : public CPUThread {
public:
    MockCPUThread() : CPUThread(nullptr, nullptr, nullptr) {
        this->ram = std::make_unique<RAM>();
        this->regs = CPURegisters();
        this->regs.clear();
    }

    CPURegisters* get_regs() override { return &this->regs; };
    RAM* get_ram() override { return this->ram.get(); };


private:
    CPURegisters regs;
    std::unique_ptr<RAM> ram;
};


TEST(RV32ITEST, ADDI_TO_INSTR){
    ADDI addi = ADDI(1, 2, 3);
    uint32_t instr = addi.to_instruction();

    EXPECT_EQ(bits(instr, 0, 6), 0b0010011);            // opcode
    EXPECT_EQ(bits(instr, 7, 11), 3);                   // dest reg
    EXPECT_EQ(bits(instr, 12, 14), 0);                  // ADDI code
    EXPECT_EQ(bits(instr, 15, 19), 1);                  // src reg
    EXPECT_EQ(extract_imm_signed32(instr, ImmType::I), 2);// immediate
}

Comp* make_comp(){
	InstructionParser* parser = new InstructionParser();
	parser->register_isa(isa_rv32i());

	return new Comp(*parser);
}

TEST(RV32ITEST, ADDI_PARSER) {
    Comp* comp = make_comp();
    ADDI addi = ADDI(1, 2, 3);
    uint32_t instr = addi.to_instruction();
    RVUnparsedInstrUnion instr_union;
    instr_union.instr_32 = instr;
    RVUnparsedInstr unparsed_instr = RVUnparsedInstr(RVUnparsedInstrType::INSTR32, instr_union);

    std::unique_ptr<AInstruction> parsed_instr = comp->get_cpu()->get_parser()->parse(unparsed_instr);

    EXPECT_EQ(instr, parsed_instr->to_instruction());

    addi = ADDI(1, -2, 3);
    instr = addi.to_instruction();
    instr_union.instr_32 = instr;
    unparsed_instr = RVUnparsedInstr(RVUnparsedInstrType::INSTR32, instr_union);

    parsed_instr = comp->get_cpu()->get_parser()->parse(unparsed_instr);

    EXPECT_EQ(instr, parsed_instr->to_instruction());
}

TEST(ADDTest, ExecutePos) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 10);
    thread.get_regs()->set_ri(2, 20);

    ADD add_instr(1, 2, 3);
    add_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(3), 30);
}

TEST(ADDTest, ExecuteNeg) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 10);
    thread.get_regs()->set_ri(2, -20);

    ADD add_instr(1, 2, 3);
    add_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(3), -10);
}
TEST(SUBTest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 30);
    thread.get_regs()->set_ri(2, 10);

    SUB sub_instr(1, 2, 3);
    sub_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(3), 20);
}

TEST(ADDITest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 10);

    ADDI addi_instr(1, 5, 2);
    addi_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(2), 15);
}

TEST(SLLITest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 1);

    SLLI slli_instr(1, 2, 2);
    slli_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(2), 4);
}

TEST(SLTITest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 5);

    SLTI slti_instr(1, 10, 2);
    slti_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(2), 1);
}

TEST(SLTIUTest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 5);

    SLTIU sltiu_instr(1, 10, 2);
    sltiu_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(2), 1);
}

TEST(XORITest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 0b1010);

    XORI xori_instr(1, 0b0101, 2);
    xori_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(2), 0b1111);
}

TEST(ANDITest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 0b1010);

    ANDI andi_instr(1, 0b1100, 2);
    andi_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(2), 0b1000);
}

TEST(SRLITest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 0b1000);

    SRLI srli_instr(1, 2, 2);
    srli_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(2), 0b0010);
}

TEST(SRAITest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, -8);

    SRAI srai_instr(1, 2, 2);
    srai_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(2), -2);
}

TEST(ORITest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 0b1010);

    ORI ori_instr(1, 0b0101, 2);
    ori_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(2), 0b1111);
}

TEST(SLLTest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 1);
    thread.get_regs()->set_ri(2, 2);

    SLL sll_instr(1, 2, 3);
    sll_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(3), 4);
}

TEST(SLTTest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 5);
    thread.get_regs()->set_ri(2, 10);

    SLT slt_instr(1, 2, 3);
    slt_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(3), 1);
}

TEST(SLTUTest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 5);
    thread.get_regs()->set_ri(2, 10);

    SLTU sltu_instr(1, 2, 3);
    sltu_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(3), 1);
}

TEST(XORTest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 0b1010);
    thread.get_regs()->set_ri(2, 0b0101);

    XOR xor_instr(1, 2, 3);
    xor_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(3), 0b1111);
}

TEST(SRLTest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 0b1000);
    thread.get_regs()->set_ri(2, 2);

    SRL srl_instr(1, 2, 3);
    srl_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(3), 0b0010);
}

TEST(SRATest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, -8);
    thread.get_regs()->set_ri(2, 2);

    SRA sra_instr(1, 2, 3);
    sra_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(3), -2);
}

TEST(ORTest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 0b1010);
    thread.get_regs()->set_ri(2, 0b0101);

    OR or_instr(1, 2, 3);
    or_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(3), 0b1111);
}

TEST(ANDTest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 0b1010);
    thread.get_regs()->set_ri(2, 0b1100);

    AND and_instr(1, 2, 3);
    and_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(3), 0b1000);
}

TEST(LUITest, Execute) {
    MockCPUThread thread;

    LUI lui_instr(0x12345, 1);
    lui_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(1), 0x12345);
}

TEST(AUIPCTest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->pc = 0x1000;

    AUIPC auipc_instr(0x1234, 1);
    auipc_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(1), 0x2234);
}

TEST(BEQTest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 10);
    thread.get_regs()->set_ri(2, 10);

    BEQ beq_instr(1, 2, 4);
    EXPECT_EQ(beq_instr.execute(&thread).pc_offset, 4);
}

TEST(BNETest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 10);
    thread.get_regs()->set_ri(2, 20);

    BNE bne_instr(1, 2, 4);
    EXPECT_EQ(bne_instr.execute(&thread).pc_offset, 4);
}

TEST(BLTTest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 5);
    thread.get_regs()->set_ri(2, 10);

    BLT blt_instr(1, 2, 4);
    EXPECT_EQ(blt_instr.execute(&thread).pc_offset, 4);
}

TEST(BGTTest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 10);
    thread.get_regs()->set_ri(2, 5);

    BGT bgt_instr(1, 2, 4);
    EXPECT_EQ(bgt_instr.execute(&thread).pc_offset, 4);
}

TEST(BGETest, ExecuteGT) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 10);
    thread.get_regs()->set_ri(2, 5);

    BGE bgt_instr(1, 2, 8);
    EXPECT_EQ(bgt_instr.execute(&thread).pc_offset, 8);
}

TEST(BGETest, ExecuteGTE) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 10);
    thread.get_regs()->set_ri(2, 10);

    BGE bgt_instr(1, 2, 8);
    EXPECT_EQ(bgt_instr.execute(&thread).pc_offset, 8);
}

TEST(BGETest, ExecuteLT) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 5);
    thread.get_regs()->set_ri(2, 10);

    BGE bgt_instr(1, 2, 8);
    EXPECT_EQ(bgt_instr.execute(&thread).pc_offset, 4);
}
TEST(LOADTest, Execute) {
    MockCPUThread thread;
    thread.get_ram()->set_w(0x100, 0x12345678);
    thread.get_regs()->set_ri(1, 0x100);

    LOAD load_instr(1, LoadType::LW, 2, 0);
    load_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(2), 0x12345678);
}

TEST(STORETest, Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(1, 0x100);
    thread.get_regs()->set_ri(2, 0x12345678);

    STORE store_instr(2, 1, StoreType::SW, 0);
    store_instr.execute(&thread);

    EXPECT_EQ(thread.get_ram()->get_w(0x100), 0x12345678);
}