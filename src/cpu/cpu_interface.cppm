module;
#include <cstdint>
#include <array>

import registers;
import alu;
import memory.bus;

export module cpu.interface;

export enum class Register8Name { R0, R1, R2, R3, R4, R5, R6, R7, A, B, SP};
export enum class Register16Name { PC, DPTR };
export enum class FlagName { PSW };

export class CPU
{
public:
    CPU(MemoryBus& bus);
    
    void reset();
    void step();
    
    uint8_t fetch8();
    uint16_t fetch16();

    Register8& get(Register8Name r);
    const Register8& get(Register8Name r) const;

    Register16& get(Register16Name r);
    const Register16& get(Register16Name r) const;

    FlagRegister& get(FlagName f);
    const FlagRegister& get(FlagName f) const;

    ALU& get_alu();
private:
    MemoryBus& bus;
    ALU alu;

    Register8 acc{"A"};        // Accumulator A
    Register8 b{"B"};          // Register B
    Register8 sp{"SP"};        // Stack Pointer
    Register16 pc{"PC"};       // Program Counter
    Register16 dptr{"DPTR"};   // Data Pointer
    FlagRegister psw{"PSW"};   // Program Status Word

    using RegisterBank = std::array<Register8, 8>;
    RegisterBank rbank{Register8("R0"), Register8("R1"), Register8("R2"), Register8("R3"),
                       Register8("R4"), Register8("R5"), Register8("R6"), Register8("R7")}; // Register bank R0 - R7

    using Instruction = void (*)(CPU&);
    using Instructions = std::array<Instruction, 256>;
    Instructions dispatch_table{};

    void build_dispatch_table();
    static void operation_unimplemented(CPU&);
};