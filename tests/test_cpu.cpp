#include <catch2/catch_test_macros.hpp>
import cpu;

TEST_CASE("CPU reset initializes registers to correct default values")
{
    CPU cpu;
    cpu.reset();

    // Accumulator
    REQUIRE(cpu.get_register("A").read() == 0x00);

    // B register
    REQUIRE(cpu.get_register("B").read() == 0x00);

    // Stack pointer
    REQUIRE(cpu.get_register("SP").read() == 0x07);

    // PSW
    REQUIRE(cpu.get_register("PSW").read() == 0x00);

    // PC

    // DPTR

    // Bank Register
    for (int i = 0; i < 8; ++i)
        REQUIRE(cpu.get_register("R" + std::to_string(i)).read() == 0x00);
}