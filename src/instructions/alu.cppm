module;
#include <array>
#include <cstdint>
#include <iostream>

import cpu.context;
import cpu.alu;
import memory.bus;

export module instructions.alu;

export void register_alu_instructions(std::array<void(*)(CpuContext&), 256>& table);

// NOP (0x00)
static void op_nop(CpuContext&) {}

// INC A (0x04)
static void op_inc_a(CpuContext& context)
{
    auto& a = context.registers.acc;
    a.write(context.alu.execute(ALUOperation::INC, a.read(), 0));
}

// ADD A, #imm (0x24)
static void op_add_a_imm(CpuContext& context)
{
    auto& a = context.registers.acc;
    uint8_t imm = context.fetcher.fetch8();
    a.write(context.alu.execute(ALUOperation::ADD, a.read(), imm));
}

// ADDC A, #imm (0x34)
static void op_addc_a_imm(CpuContext& context)
{
    auto& a = context.registers.acc;
    uint8_t imm = context.fetcher.fetch8();
    a.write(context.alu.execute(ALUOperation::ADDC, a.read(), imm));
}

export void register_alu_instructions(std::array<void(*)(CpuContext&), 256>& table)
{
    table[0x00] = &op_nop;
    table[0x04] = &op_inc_a;
    table[0x24] = &op_add_a_imm;
    table[0x34] = &op_addc_a_imm;
}
