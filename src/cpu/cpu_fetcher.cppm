module;
#include <cstdint>
#include <array>

export module cpu.fetcher;

import memory.bus;
import registers;

export class InstructionFetcher
{
public:
    InstructionFetcher(MemoryBus& bus, Register16& pc)
        : bus(bus), pc(pc)
    {}
    
    uint8_t fetch8()
    {
        uint8_t addr = pc.read();
        uint8_t val = bus.read(addr);
        pc.write(addr + 1);
        return val;
    }

    uint16_t fetch16()
    {
        uint16_t lo = fetch8();
        uint16_t hi = fetch8();
        return (hi<<8)|lo;
    }

private:
    MemoryBus& bus;
    Register16& pc;
};