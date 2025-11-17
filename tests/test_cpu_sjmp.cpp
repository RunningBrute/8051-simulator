#include <catch2/catch_test_macros.hpp>

import cpu;
import memory;
import memory_bus;

namespace
{
    RAM ram(256);
    ROM rom(256);
    MemoryBus bus(ram, rom);
}

static CPU make_cpu_with_program(std::initializer_list<uint8_t> bytes)
{
    CPU cpu(bus);
    cpu.reset();

    size_t addr = 0;
    for (auto b : bytes)
        rom.data()[addr++] = b;

    return cpu;
}

TEST_CASE("SJMP $ loops (PC stays the same)", "[cpu][sjmp]")
{
    //Program: SJMP $
    auto cpu = make_cpu_with_program({0x80, 0xFE});

    cpu.step();
    REQUIRE(cpu.get(Register16Name::PC).read() == 0);
}
