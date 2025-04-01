#include <gtest/gtest.h>
#include <comp.hpp>
#include <rv32i.hpp>
#include "utils.hpp"

Comp* make_comp(){
	InstructionParser* parser = new InstructionParser();
	parser->register_isa(isa_rv32i());

	return new Comp(*parser);
}


TEST(RV32ITEST, ADDI_TO_INSTR){
    ADDI addi = ADDI(1, 2, 3);
    uint32_t instr = addi.to_instruction();

    EXPECT_EQ(bits(instr, 0, 6), 0b0010011);            // opcode
    EXPECT_EQ(bits(instr, 7, 11), 3);                   // dest reg
    EXPECT_EQ(bits(instr, 12, 14), 0);                  // ADDI code
    EXPECT_EQ(bits(instr, 15, 19), 1);                  // src reg
    EXPECT_EQ(extract_imm_signed32(instr, ImmType::I), 2);// immediate
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


TEST(RV32ITEST, ADD_POSITIVE) {
    Comp* comp = make_comp();
    comp->get_cpu()->get_core()->get_thread()->get_regs()->set_ri(1, 1);
    comp->get_cpu()->get_core()->get_thread()->get_regs()->set_ri(2, 2);

    ADD add_instr = ADD(1, 2, 3);

    add_instr.execute(comp->get_cpu()->get_core()->get_thread());

    EXPECT_EQ(comp->get_cpu()->get_core()->get_thread()->get_regs()->get_ri(1), 1);
    EXPECT_EQ(comp->get_cpu()->get_core()->get_thread()->get_regs()->get_ri(2), 2);
    EXPECT_EQ(comp->get_cpu()->get_core()->get_thread()->get_regs()->get_ri(3), 3);

    delete comp;
}


TEST(RV32ITEST, ADD_NEGATIVE) {
    Comp* comp = make_comp();
    comp->get_cpu()->get_core()->get_thread()->get_regs()->set_ri(1, 1);
    comp->get_cpu()->get_core()->get_thread()->get_regs()->set_ri(2, -2);

    ADD add_instr = ADD(1, 2, 3);

    add_instr.execute(comp->get_cpu()->get_core()->get_thread());

    EXPECT_EQ(comp->get_cpu()->get_core()->get_thread()->get_regs()->get_ri(1), 1);
    EXPECT_EQ(comp->get_cpu()->get_core()->get_thread()->get_regs()->get_ri(2), -2);
    EXPECT_EQ(comp->get_cpu()->get_core()->get_thread()->get_regs()->get_ri(3), -1);

    delete comp;
}