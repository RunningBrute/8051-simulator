module;
#include <span>
#include <cstdint>

export module system;

import cpu;
import memory;
import memory.bus;
import io;

export class System
{
public:
    System()
        : ram(128), rom(4096),
          bus(ram, rom),
          cpu(bus)
    {}

    void reset()
    {
        cpu.reset();
        ram = RAM(128);
        rom = ROM(4096);
    }

    RAM ram;
    ROM rom;
    IO io;
    MemoryBus bus;
    CPU cpu;
};