module;
#include <array>
#include <string>
#include <cstdint>
#include <iostream>
#include <span>

import registers.register8;
import registers.register16;
import registers.flag_register;

export module cpu;

using RegisterBank = std::array<Register8, 8>;

export enum class Register8Name { R0, R1, R2, R3, R4, R5, R6, R7, A, B, SP};
export enum class Register16Name { PC, DPTR };
export enum class FlagName { PSW };

export class CPU
{
public:
    CPU(std::span<uint8_t> memory);
    
    void reset();
    void step();
    
    Register8& get(Register8Name r);
    const Register8& get(Register8Name r) const;

    Register16& get(Register16Name r);
    const Register16& get(Register16Name r) const;

    FlagRegister& get(FlagName f);
    const FlagRegister& get(FlagName f) const;
private:

    Register8 acc{"A"};        // Accumulator A
    Register8 b{"B"};          // Register B
    Register8 sp{"SP"};        // Stack Pointer
    Register16 pc{"PC"};       // Program Counter
    Register16 dptr{"DPTR"};   // Data Pointer
    FlagRegister psw{"PSW"};   // Program Status Word
    RegisterBank rbank{Register8("R0"), Register8("R1"), Register8("R2"), Register8("R3"),
                       Register8("R4"), Register8("R5"), Register8("R6"), Register8("R7")}; // Register bank R0 - R7

    std::span<uint8_t> memory;

    uint8_t fetch8();
    uint16_t fetch16();
};

module :private;

CPU::CPU(std::span<uint8_t> memory) 
    : memory(memory)
{}

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
    auto opcode = fetch8();

    switch(opcode)
    {
        case 0x00: // NOP
            return;
        default:
            throw std::runtime_error("Unimplemented opcode");
    }
}

uint8_t CPU::fetch8()
{
    uint8_t v = memory[pc.read()];
    pc.write(pc.read()+1);
    return v;
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
   