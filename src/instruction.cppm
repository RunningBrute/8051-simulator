module;
#include <cstdint>

export module instruction;

import cpu;
import memory;

export struct Instruction
{
    uint8_t opcode;
    const char* name;
    void (*execute)(CPU&, Memory&);
};