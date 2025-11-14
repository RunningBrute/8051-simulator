#include <iostream>

import assembler;
import system;

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: f.e. 8051-simulator.exe example/mov_test.asm" << std::endl;
        return 1;
    }

    Assembler assembler;
    System system;

    auto program = assembler.assemble_file(argv[1]);
    system.load_program(program);
    system.reset();

    std::cout << "8051 Simulator started";
    for (;;)
    {
        std::cout << " . ";
        system.cpu.step();
    }

    return 0;
}