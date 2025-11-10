module;
#include <array>
#include <cstdint>
#include <iostream>

import cpu.interface;
import registers;
import memory.bus;

export module instructions.data;

export void register_data_instructions(std::array<void(*)(CPU&), 256>& table);


// MOV A, #imm (0x74)
static void op_mov_a_imm(CPU& cpu)
{
    uint8_t imm = cpu.fetch8();
    cpu.get(Register8Name::A).write(imm);
}

// MOV direct, A (0xF5)
static void op_mov_direct_a(CPU& cpu)
{
    uint8_t addr = cpu.fetch8();
    uint8_t value = cpu.get(Register8Name::A).read();
    cpu.get_bus().write(0x1000 + addr, value); 
    cpu.fetch8(); // just for debug logs
}

// MOV A, direct (0xE5)
static void op_mov_a_direct(CPU& cpu)
{
    uint8_t addr = cpu.fetch8();
    uint8_t value = cpu.get_bus().read(0x1000 + addr);
    cpu.get(Register8Name::A).write(value);
}

export void register_data_instructions(std::array<void(*)(CPU&), 256>& table)
{
    table[0x74] = &op_mov_a_imm;
    table[0xF5] = &op_mov_direct_a;
    table[0xE5] = &op_mov_a_direct;
}
