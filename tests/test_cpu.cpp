#include <catch2/catch_test_macros.hpp>

import cpu;
import memory;
import memory.bus;

TEST_CASE("CPU reset sets all registers to their default state", "[cpu]")
{
    RAM ram(128);
    ROM rom(4096);
    MemoryBus bus(ram, rom);
    CPU cpu(bus);

    cpu.get_context().registers.acc.write(0xFF);
    cpu.get_context().registers.b.write(0xFF);
    cpu.get_context().registers.rbank.rbank[0].write(0xFF);
    cpu.get_context().registers.rbank.rbank[7].write(0xFF);

    cpu.reset();

    REQUIRE(cpu.get_context().registers.acc.read() == 0x00);
    REQUIRE(cpu.get_context().registers.b.read() == 0x00);

    for (std::size_t i = 0; i < 8; i++)
    {
        REQUIRE(cpu.get_context().registers.rbank.rbank[i].read() == 0x00);
    }

    REQUIRE(cpu.get_context().registers.sp.read() == 0x07);
    REQUIRE(cpu.get_context().registers.pc.read() == 0x0000);
    REQUIRE(cpu.get_context().registers.dptr.read() == 0x0000);
    REQUIRE(cpu.get_context().registers.psw.read() == 0x00);
}

TEST_CASE("CPU executes NOP instruction incrementing PC", "[cpu][fetch]")
{
    RAM ram(128);
    ROM rom(4096);
    MemoryBus bus(ram, rom);

    std::vector<uint8_t> program = {0x00};
    rom.load(program);

    CPU cpu(bus);
    cpu.reset();

    REQUIRE(cpu.get_context().registers.pc.read() == 0x0000);
    cpu.step();
    REQUIRE(cpu.get_context().registers.pc.read() == 0x0001);
}

