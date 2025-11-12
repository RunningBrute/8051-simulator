#include <catch2/catch_test_macros.hpp>

import system;
import cpu;
import memory;
import memory.bus;

TEST_CASE("System constructor wires RAM, ROM, and CPU correctly", "[system]")
{
    System sys;

    sys.ram.write(10, 0xAB);
    REQUIRE(sys.bus.read(0x100A) == 0xAB);

    REQUIRE_NOTHROW(sys.bus.read(0x0000));
}

TEST_CASE("System reset resets CPU registers and RAM", "[system]")
{
    System sys;

    sys.cpu.get_context().registers.acc.write(0x99);
    sys.ram.write(20, 0x44);

    sys.reset();

    REQUIRE(sys.cpu.get_context().registers.acc.read() == 0x00);
    REQUIRE(sys.cpu.get_context().registers.sp.read() == 0x07);
    REQUIRE(sys.ram.read(20) == 0x00);
}

TEST_CASE("System reset resets PC and DPTR", "[system]")
{
    System sys;

    sys.cpu.get_context().registers.pc.write(0x1234);
    sys.cpu.get_context().registers.dptr.write(0xABCD);

    sys.reset();

    REQUIRE(sys.cpu.get_context().registers.pc.read() == 0x0000);
    REQUIRE(sys.cpu.get_context().registers.dptr.read() == 0x0000);
}

TEST_CASE("System ROM remains read-only after reset", "[system]")
{
    System sys;
    REQUIRE_THROWS(sys.bus.write(0x0000, 0xAA)); // ROM = read-only
}
