#include <catch2/catch_test_macros.hpp>

import cpu;
import memory;
import memory.bus;

TEST_CASE("CPU executes ADD A, #imm correctly", "[cpu][add]")
{
    RAM ram(256);
    ROM rom(256);
    MemoryBus bus(ram, rom);
    CPU cpu(bus);

    cpu.reset();

    // Program: ADD A, #0x10 ; NOP
    rom.data()[0x0000] = 0x24; // opcode
    rom.data()[0x0001] = 0x10; // immediate operand
    rom.data()[0x0002] = 0x00; // NOP (just to stop)

    auto& A = cpu.get(Register8Name::A);
    A.write(0x22);

    cpu.step(); // execute ADD A, #0x10

    REQUIRE(A.read() == 0x32);

    auto& PSW = cpu.get(FlagName::PSW);
    REQUIRE_FALSE(PSW.carry());
    REQUIRE_FALSE(PSW.overflow());
    REQUIRE_FALSE(PSW.aux_carry());
}

TEST_CASE("ADD A, #imm sets carry and overflow correctly", "[cpu][add][flags]")
{
    RAM ram(256);
    ROM rom(256);
    MemoryBus bus(ram, rom);
    CPU cpu(bus);

    cpu.reset();

    // Program: ADD A, #0x80
    rom.data()[0] = 0x24;
    rom.data()[1] = 0x80;

    auto& A = cpu.get(Register8Name::A);
    A.write(0x80); // 0x80 + 0x80 = 0x100

    cpu.step();

    auto& PSW = cpu.get(FlagName::PSW);

    REQUIRE(A.read() == 0x00);        // overflowed
    REQUIRE(PSW.carry());             // carry set
    REQUIRE(PSW.overflow());          // overflow set (sign flipped)
}