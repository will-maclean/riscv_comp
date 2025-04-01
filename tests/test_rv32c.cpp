#include <gtest/gtest.h>
#include <comp.hpp>
#include "rv32i.hpp"
#include "rv32c.hpp"
#include "utils.hpp"
#include "cpu.hpp"
#include "instructions.hpp"

class MockCPUThread : public CPUThread {
public:
    MockCPUThread() : CPUThread(nullptr, nullptr) {
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

Comp* make_comp_rv32c() {
    InstructionParser* parser = new InstructionParser();
    parser->register_isa(isa_rv32c());

    return new Comp(*parser);
}

TEST(RV32CTEST, ADDI4SPN_Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(2, 0x1000);

    ADDI addi_instr(10, 16, 2, 2); // c.addi4spn
    addi_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(10), 0x1010);
}

TEST(RV32CTEST, LWSP_Execute) {
    MockCPUThread thread;
    thread.get_ram()->set_w(0x1004, 0x12345678);
    thread.get_regs()->set_ri(2, 0x1000);

    LOAD lwsp_instr(5, LoadType::LW, 2, 4, 2); // c.lwsp
    lwsp_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(5), 0x12345678);
}

TEST(RV32CTEST, SWSP_Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(2, 0x1000);
    thread.get_regs()->set_ri(10, 0x12345678);

    STORE swsp_instr(10, 2, StoreType::SW, 4, 2); // c.swsp
    swsp_instr.execute(&thread);

    EXPECT_EQ(thread.get_ram()->get_w(0x1004), 0x12345678);
}

TEST(RV32CTEST, JAL_Execute) {
    MockCPUThread thread;
    thread.get_regs()->pc = 0x1000;

    JAL jal_instr(1, 0x10, 2); // c.jal
    auto result = jal_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(1), 0x1004); // Return address
    EXPECT_EQ(result.pc_offset, 0x10);
}

TEST(RV32CTEST, BEQZ_Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(8, 0);

    BEQ beqz_instr(8, 0, 0x8, 2); // c.beqz
    auto result = beqz_instr.execute(&thread);

    EXPECT_EQ(result.pc_offset, 0x8);
}

TEST(RV32CTEST, BNEZ_Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(8, 1);

    BNE bnez_instr(8, 0, 0x8, 2); // c.bnez
    auto result = bnez_instr.execute(&thread);

    EXPECT_EQ(result.pc_offset, 0x8);
}

TEST(RV32CTEST, SLLI_Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(5, 1);

    SLLI slli_instr(5, 5, 2, 2); // c.slli
    slli_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(5), 4);
}

TEST(RV32CTEST, ANDI_Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(8, 0b1010);

    ANDI andi_instr(8, 8, 0b1100, 2); // c.andi
    andi_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(8), 0b1000);
}

TEST(RV32CTEST, SUB_Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(8, 10);
    thread.get_regs()->set_ri(9, 5);

    SUB sub_instr(8, 9, 8, 2); // c.sub
    sub_instr.execute(&thread);

    EXPECT_EQ(thread.get_regs()->get_ri(8), 5);
}

TEST(RV32CTEST, JR_Execute) {
    MockCPUThread thread;
    thread.get_regs()->set_ri(8, 0x2000);

    JALR jr_instr(8, 0, 0, 2); // c.jr
    auto result = jr_instr.execute(&thread);

    EXPECT_EQ(result.pc_offset, 0x2000);
}
