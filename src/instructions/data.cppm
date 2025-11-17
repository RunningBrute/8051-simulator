module;
#include <array>
#include <cstdint>
#include <iostream>

import cpu.context;
import registers;
import memory.bus;

export module instructions.data;

export void register_data_instructions(std::array<void(*)(CpuContext&), 256>& table);


// MOV A, #imm (0x74)
static void op_mov_a_imm(CpuContext& context)
{
    uint8_t imm = context.fetcher.fetch8();
    context.registers.acc.write(imm);
}

// MOV direct, A (0xF5)
static void op_mov_direct_a(CpuContext& context)
{
    uint8_t addr = context.fetcher.fetch8();
    uint8_t value = context.registers.acc.read();
    context.bus.write(0x1000 + addr, value); 
    context.fetcher.fetch8(); // just for debug logs
}

// MOV A, direct (0xE5)
static void op_mov_a_direct(CpuContext& context)
{
    uint8_t addr = context.fetcher.fetch8();
    uint8_t value = context.bus.read(0x1000 + addr);
    context.registers.acc.write(value);
}

// SJMP $
static void op_sjmp(CpuContext& context) {
    int8_t rel = context.fetcher.fetch8();
    uint16_t pc = context.registers.pc.read();
    context.registers.pc.write(pc + rel);
}

export void register_data_instructions(std::array<void(*)(CpuContext&), 256>& table)
{
    table[0x74] = &op_mov_a_imm;
    table[0xF5] = &op_mov_direct_a;
    table[0xE5] = &op_mov_a_direct;
    table[0x80] = &op_sjmp;
}
