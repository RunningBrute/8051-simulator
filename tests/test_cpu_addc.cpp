#include <catch2/catch_test_macros.hpp>
import cpu;
import memory.bus;
import memory;

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

TEST_CASE("ADDC A,#imm adds with carry correctly", "[cpu][addc][flags]")
{
    // Program: ADDC A,#0x10
    auto cpu = make_cpu_with_program({0x34, 0x10});

    auto& A = cpu.get_context().registers.acc;
    auto& PSW = cpu.get_context().registers.psw;

    A.write(0x05);
    PSW.set_carry(true); // carry-in = 1

    cpu.step();

    REQUIRE(A.read() == 0x16); // 0x05 + 0x10 + 1
    REQUIRE_FALSE(PSW.overflow());
    REQUIRE_FALSE(PSW.aux_carry());
    REQUIRE_FALSE(PSW.carry());
}

TEST_CASE("ADDC A,#imm sets carry and overflow when needed", "[cpu][addc][flags]")
{
    // Program: ADDC A,#0x80
    auto cpu = make_cpu_with_program({0x34, 0x80});

    auto& A = cpu.get_context().registers.acc;
    auto& PSW = cpu.get_context().registers.psw;

    A.write(0x80);
    PSW.set_carry(false);

    cpu.step(); // 0x80 + 0x80 + 0 = 0x100

    REQUIRE(A.read() == 0x00);
    REQUIRE(PSW.carry());
    REQUIRE(PSW.overflow());
}

TEST_CASE("ADDC performs proper multi-byte addition (16-bit add)", "[cpu][addc]")
{
    // Program:
    //  0000: 24 LL   ADD A,#low
    //  0002: 34 HH   ADDC A,#high
    auto cpu = make_cpu_with_program({0x24, 0xFF, 0x34, 0x01});

    auto& A = cpu.get_context().registers.acc;
    auto& PSW = cpu.get_context().registers.psw;

    // emulate 16-bit add: low=0xFF + 0x01 → carry, then high+carry
    A.write(0x00);

    cpu.step();  // ADD A,#0xFF
    REQUIRE(A.read() == 0xFF);
    REQUIRE_FALSE(PSW.carry());

    cpu.step();  // ADDC A,#0x01
    REQUIRE(A.read() == 0x00); // 0xFF + 0x01 = 0x100 → 0x00
    REQUIRE(PSW.carry());      // carry should propagate
}

TEST_CASE("ADDC chain propagates carry correctly through multiple operations", "[cpu][addc]")
{
    // Program:
    //  0000: 34 01  ADDC A,#1  
    //  0002: 34 01  ADDC A,#1
    //  0004: 34 01  ADDC A,#1 
    auto cpu = make_cpu_with_program({0x34, 0x01, 0x34, 0x01, 0x34, 0x01});

    auto& A = cpu.get_context().registers.acc;
    auto& PSW = cpu.get_context().registers.psw;

    A.write(0xFE);
    PSW.set_carry(true); // start with carry=1

    cpu.step(); // FE + 01 + 1 = 0x00, carry = 1
    REQUIRE(A.read() == 0x00);
    REQUIRE(PSW.carry());

    cpu.step(); // 00 + 01 + 1 = 0x02, carry cleared
    REQUIRE(A.read() == 0x02);
    REQUIRE_FALSE(PSW.carry());

    cpu.step(); // 02 + 01 = 0x03, carry still 0
    REQUIRE(A.read() == 0x03);
    REQUIRE_FALSE(PSW.carry());
}
