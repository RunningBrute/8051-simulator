#include <array>
#include <string>
#include <cstdint>
#include <iostream>

import register8;
import register16;

export module cpu;

export class CPU
{
public:
    CPU();
    void reset();
    Register get_register(const std::string& name) const;
private:
    Register acc{"A"};         // Accumulator A
    Register b{"B"};           // Register B
    Register psw{"PSW"};       // Program Status Word
    Register sp{"SP"};         // Stack Pointer
    Register16 pc{"PC"};       // Program Counter
    Register16 dptr{"DPTR"};   // Data Pointer
    std::array<Register, 8> r{Register("R0"), Register("R1"), Register("R2"), Register("R3"),
                              Register("R4"), Register("R5"), Register("R6"), Register("R7")}; // R0–R7
};

module :private;

CPU::CPU()
{
}

void CPU::reset()
{
}

Register CPU::get_register(const std::string& name) const
{
    return acc;
}