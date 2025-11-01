#include <array>
#include <string>
#include <cstdint>
#include <iostream>

import register8;
import register16;
import flag_register;

export module cpu;

using RegisterBank = std::array<Register8, 8>;

export class CPU
{
public:
    CPU();
    void reset();
    Register8 get_register(const std::string& name) const;
private:
    Register8 acc{"A"};         // Accumulator A
    Register8 b{"B"};           // Register B
    Register8 sp{"SP"};         // Stack Pointer
    Register16 pc{"PC"};       // Program Counter
    Register16 dptr{"DPTR"};   // Data Pointer
    FlagRegister psw{"PSW"};   // Program Status Word
    RegisterBank rb{Register8("R0"), Register8("R1"), Register8("R2"), Register8("R3"),
                    Register8("R4"), Register8("R5"), Register8("R6"), Register8("R7")}; // Register bank R0 - R7
};

module :private;

CPU::CPU()
{
}

void CPU::reset()
{
    acc.write(0x00);
    b.write(0x00);
    sp.write(0x07);
    pc.write(0x0000);
    dptr.write(0x0000);
    psw.write(0x00);
    for (auto& r : rb)
        r.write(0x00);
}

Register8 CPU::get_register(const std::string& name) const
{
    if (name == "A") return acc;
    if (name == "B") return b;
    if (name == "SP") return sp;

    for (size_t i = 0; i < rb.size(); ++i)
        if (name == ("R" + std::to_string(i))) return rb[i];

    return acc;
}