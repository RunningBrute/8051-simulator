module;
#include <span>
#include <cstdint>
#include <vector>

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

    void load_program(const std::vector<uint8_t>& program)
    {
        rom.load(program);
    }

    RAM ram;
    ROM rom;
    IO io;
    MemoryBus bus;
    CPU cpu;
};