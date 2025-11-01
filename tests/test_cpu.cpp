#include <catch2/catch_test_macros.hpp>

import cpu;

TEST_CASE("CPU reset sets all registers to initial values", "[cpu]")
{
    CPU cpu;

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