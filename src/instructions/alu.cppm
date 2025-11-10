module;
#include <array>
#include <cstdint>
#include <iostream>

import alu;
import cpu.interface;
import registers;

export module instructions.alu;

export void register_alu_instructions(std::array<void(*)(CPU&), 256>& table);

// NOP (0x00)
static void op_nop(CPU&) {}

// INC A (0x04)
static void op_inc_a(CPU& cpu)
{
    auto& a = cpu.get(Register8Name::A);
    auto& alu = cpu.get_alu();
    a.write(alu.execute(ALUOperation::INC, a.read(), 0));
}

// ADD A, #imm (0x24)
static void op_add_a_imm(CPU& cpu)
{
    auto& a = cpu.get(Register8Name::A);
    uint8_t imm = cpu.fetch8();
    a.write(cpu.get_alu().execute(ALUOperation::ADD, a.read(), imm));
}

// ADDC A, #imm (0x34)
static void op_addc_a_imm(CPU& cpu)
{
    auto& a = cpu.get(Register8Name::A);
    uint8_t imm = cpu.fetch8();
    a.write(cpu.get_alu().execute(ALUOperation::ADDC, a.read(), imm));
}

export void register_alu_instructions(std::array<void(*)(CPU&), 256>& table)
{
    table[0x00] = &op_nop;
    table[0x04] = &op_inc_a;
    table[0x24] = &op_add_a_imm;
    table[0x34] = &op_addc_a_imm;
}
