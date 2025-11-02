#include <span>

export module system;

import cpu;
import memory;
import io;

export class System
{
public:
    System();
    void reset();

    CPU cpu;
    Memory memory;
    IO io;
};

module :private;

System::System()
    : memory(),
      cpu(std::span<uint8_t>(memory.data(), memory.size()))
{}

void System::reset()
{
    cpu.reset();
    memory = Memory{};
    io = IO{};
}