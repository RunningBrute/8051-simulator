#include <catch2/catch_test_macros.hpp>

import cpu.interface;
import memory;
import memory.bus;

TEST_CASE("CPU reset sets all registers to their default state", "[cpu]")
{
    RAM ram(128);
    ROM rom(4096);
    MemoryBus bus(ram, rom);
    CPU cpu(bus);

    cpu.get(Register8Name::A).write(0xFF);
    cpu.get(Register8Name::B).write(0xFF);
    cpu.get(Register8Name::R0).write(0xFF);
    cpu.get(Register8Name::R7).write(0xFF);

    cpu.reset();

    REQUIRE(cpu.get(Register8Name::A).read() == 0x00);
    REQUIRE(cpu.get(Register8Name::B).read() == 0x00);

    for (auto r : {Register8Name::R0, Register8Name::R1, Register8Name::R2, Register8Name::R3,
                   Register8Name::R4, Register8Name::R5, Register8Name::R6, Register8Name::R7})
    {
        REQUIRE(cpu.get(r).read() == 0x00);
    }

    REQUIRE(cpu.get(Register8Name::SP).read() == 0x07);
    REQUIRE(cpu.get(Register16Name::PC).read() == 0x0000);
    REQUIRE(cpu.get(Register16Name::DPTR).read() == 0x0000);
    REQUIRE(cpu.get(FlagName::PSW).read() == 0x00);
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

    REQUIRE(cpu.get(Register16Name::PC).read() == 0x0000);
    cpu.step();
    REQUIRE(cpu.get(Register16Name::PC).read() == 0x0001);
}
