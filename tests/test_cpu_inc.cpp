#include <catch2/catch_test_macros.hpp>

import cpu;
import memory;
import memory.bus;

TEST_CASE("CPU executes INC A correctly", "[cpu][inc]")
{
    RAM ram(256);
    ROM rom(256);
    MemoryBus bus(ram, rom);
    CPU cpu(bus);

    cpu.reset();

    // Program: INC A (0x04), NOP (0x00)
    rom.data()[0x0000] = 0x04;
    rom.data()[0x0001] = 0x00;

    auto& A = cpu.get(Register8Name::A);
    A.write(0x0F);

    cpu.step();  // execute INC A

    REQUIRE(A.read() == 0x10);
    REQUIRE(cpu.get(FlagName::PSW).parity() == false); // 0x10 = 00010000 → 1 bit → odd
}