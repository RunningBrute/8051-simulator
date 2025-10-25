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

System::System() = default;

void System::reset()
{
    cpu.reset();
    memory = Memory{};
    io = IO{};
}