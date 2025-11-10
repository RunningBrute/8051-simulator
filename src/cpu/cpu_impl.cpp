module;
#include <array>
#include <iostream>
#include <sstream>
#include <iomanip>

module cpu;

import registers;
import alu;
import memory.bus;
import instructions.alu;
import instructions.data;

CPU::CPU(MemoryBus& bus) 
    : bus(bus),
      alu(psw)
{
    build_dispatch_table();
}

void CPU::reset()
{
    acc.write(0x00);
    b.write(0x00);
    sp.write(0x07);
    pc.write(0x0000);
    dptr.write(0x0000);
    psw.write(0x00);
    for (auto& r : rbank)
        r.write(0x00);
}

void CPU::step()
{
    auto pc_val = pc.read();
    auto opcode = fetch8();
/*
    std::cout << "[DEBUG] Executing opcode 0x"
              << std::uppercase << std::hex
              << static_cast<int>(opcode)
              << " at PC=0x" << std::setw(4) << pc_val << std::endl;
*/
    auto operation = dispatch_table[opcode];

    if (operation)
        operation(*this);
    else
        operation_unimplemented(*this);
}

void CPU::operation_unimplemented(CPU& cpu)
{
    uint16_t pc_val = cpu.pc.read() - 1;
    uint8_t op = cpu.bus.read(pc_val);
    std::ostringstream oss;
    oss << "Unimplemented opcode: 0x"
        << std::uppercase << std::hex << static_cast<int>(op);
    throw std::runtime_error(oss.str());
}

void CPU::build_dispatch_table()
{
    dispatch_table.fill(nullptr);
    register_alu_instructions(dispatch_table);
    register_data_instructions(dispatch_table);
}

uint8_t CPU::fetch8()
{
    uint8_t addr = pc.read();
    uint8_t val = bus.read(addr);
    pc.write(addr + 1);
    return val;
}

uint16_t CPU::fetch16()
{
    uint16_t lo = fetch8();
    uint16_t hi = fetch8();
    return (hi<<8)|lo;
}

Register8& CPU::get(Register8Name r)
{
    switch (r)
    {
        case Register8Name::A: return acc;
        case Register8Name::B: return b;
        case Register8Name::SP: return sp;
        case Register8Name::R0: return rbank[0];
        case Register8Name::R1: return rbank[1];
        case Register8Name::R2: return rbank[2];
        case Register8Name::R3: return rbank[3];
        case Register8Name::R4: return rbank[4];
        case Register8Name::R5: return rbank[5];
        case Register8Name::R6: return rbank[6];
        case Register8Name::R7: return rbank[7];
    }
    throw std::out_of_range("Invalid 8-bit register");
}

const Register8& CPU::get(Register8Name r) const
{
    return const_cast<CPU*>(this)->get(r);
}

Register16& CPU::get(Register16Name r)
{
    switch (r)
    {
        case Register16Name::PC: return pc;
        case Register16Name::DPTR: return dptr;
    }
    throw std::out_of_range("Invalid 16-bit register");
}

const Register16& CPU::get(Register16Name r) const
{
    return const_cast<CPU*>(this)->get(r);
}

FlagRegister& CPU::get(FlagName f)
{
    switch (f)
    {
        case FlagName::PSW: return psw;
    }
    throw std::out_of_range("Invalid flag register");
}

const FlagRegister& CPU::get(FlagName f) const
{
    return const_cast<CPU*>(this)->get(f);
}

MemoryBus& CPU::get_bus()
{
    return bus;
}

const MemoryBus& CPU::get_bus() const
{
    return bus;
}

ALU& CPU::get_alu()
{
    return alu;
}
   