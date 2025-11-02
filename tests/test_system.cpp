#include <catch2/catch_test_macros.hpp>

import system;
import io;
import cpu;
import memory;

TEST_CASE("System constructor wires memory into CPU", "[system]")
{
    System sys;

    sys.memory.write(10, 0xAB);

    REQUIRE(sys.memory.read(10) == 0xAB);
}

TEST_CASE("System reset resets CPU and Memory", "[system]")
{
    System sys;

    sys.cpu.get(Register8Name::A).write(0x99);
    sys.memory.write(20, 0x44);

    sys.reset();

    REQUIRE(sys.cpu.get(Register8Name::A).read() == 0x00);
    REQUIRE(sys.cpu.get(Register8Name::SP).read() == 0x07);

    REQUIRE(sys.memory.read(20) == 0x00);
}

TEST_CASE("System reset resets PC and DPTR too", "[system]")
{
    System sys;

    sys.cpu.get(Register16Name::PC).write(0x1234);
    sys.cpu.get(Register16Name::DPTR).write(0xABCD);

    sys.reset();

    REQUIRE(sys.cpu.get(Register16Name::PC).read() == 0x0000);
    REQUIRE(sys.cpu.get(Register16Name::DPTR).read() == 0x0000);
}
