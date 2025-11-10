#include <catch2/catch_test_macros.hpp>

import cpu.interface;
import memory;
import memory.bus;

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

TEST_CASE("MOV A, #imm loads immediate into accumulator", "[cpu][mov]")
{
    // Program: 
    //  MOV A, #0x42 ; NOP
    auto cpu = make_cpu_with_program({0x74, 0x42, 0x00});

    cpu.step(); // execute MOV A, #0x42

    REQUIRE(cpu.get(Register8Name::A).read() == 0x42);
}

TEST_CASE("MOV direct, A writes accumulator to internal memory", "[cpu][mov]")
{
    // Program:
    //  MOV direct(0x20), A
    auto cpu = make_cpu_with_program({0xF5, 0x20, 0x00});

    cpu.get(Register8Name::A).write(0x99);
    cpu.step(); // execute MOV 0x20, A

    REQUIRE(ram.read(0x20) == 0x99);
}

TEST_CASE("MOV A, direct loads value from internal memory", "[cpu][mov]")
{
    ram.write(0x30, 0xAB);

    // Program:
    //  MOV A, direct(0x30)
    auto cpu = make_cpu_with_program({0xE5, 0x30, 0x00});

    cpu.step(); // execute MOV A, 0x30

    REQUIRE(cpu.get(Register8Name::A).read() == 0xAB);
}
