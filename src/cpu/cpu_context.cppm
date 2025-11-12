module;
#include <cstdint>
#include <array>

export module cpu.context;

import cpu.alu;
import memory.bus;
import cpu.registers;
import cpu.fetcher;

export struct CpuContext
{
public:
    CpuContext(MemoryBus& bus)
        : registers(), 
          bus(bus),
          alu(registers.psw),
          fetcher(bus, registers.pc)
    {}
    
    Registers registers;
    MemoryBus& bus;
    ALU alu;
    InstructionFetcher fetcher;
};