module;
#include <cstdint>
#include <array>

export module cpu.registers;

import registers;

export struct RegisterBank
{
    std::array<Register8, 8> rbank
    {   
        Register8("R0"),
        Register8("R1"),
        Register8("R2"),
        Register8("R3"),
        Register8("R4"),
        Register8("R5"),
        Register8("R6"),
        Register8("R7")
    };

    void reset()
    {
        for (auto& r : rbank)
            r.write(0x00);
    }
};

export struct Registers
{
    Register8 acc{"A"};        // Accumulator A
    Register8 b{"B"};          // Register B
    Register8 sp{"SP"};        // Stack Pointer
    Register16 pc{"PC"};       // Program Counter
    Register16 dptr{"DPTR"};   // Data Pointer
    FlagRegister psw{"PSW"};   // Program Status Word
    RegisterBank rbank;        // R0-R7 Register Banks
};