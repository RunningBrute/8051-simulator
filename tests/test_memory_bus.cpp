#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <vector>
import memory;
import memory.bus;

TEST_CASE("MemoryBus reads data from ROM correctly", "[memory][rom]")
{
    std::vector<uint8_t> program = {0x11, 0x22, 0x33, 0x44};
    ROM rom(4096);
    rom.load(program);

    RAM ram(128);
    MemoryBus bus(ram, rom);

    REQUIRE(bus.read(0x0000) == 0x11);
    REQUIRE(bus.read(0x0001) == 0x22);
    REQUIRE(bus.read(0x0003) == 0x44);
    REQUIRE(bus.read(0x0FFF) == 0x00);
}

TEST_CASE("MemoryBus reads and writes to RAM correctly", "[memory][ram]")
{
    RAM ram(128);
    ROM rom(4096);
    MemoryBus bus(ram, rom);

    bus.write(0x1000, 0xAA);
    bus.write(0x107F, 0x55);

    REQUIRE(bus.read(0x1000) == 0xAA);
    REQUIRE(bus.read(0x107F) == 0x55);

    REQUIRE(bus.read(0x2000) == 0xFF);
}

TEST_CASE("MemoryBus forbids writing into ROM", "[memory][rom]")
{
    RAM ram(128);
    ROM rom(4096);
    MemoryBus bus(ram, rom);

    REQUIRE_THROWS_AS(bus.write(0x0000, 0x77), std::runtime_error);
}

TEST_CASE("MemoryBus returns 0xFF for unmapped addresses", "[memory]")
{
    RAM ram(128);
    ROM rom(4096);
    MemoryBus bus(ram, rom);

    REQUIRE(bus.read(0x2000) == 0xFF);
}

TEST_CASE("MemoryBus exposes references to underlying memories", "[memory]")
{
    RAM ram(128);
    ROM rom(4096);
    MemoryBus bus(ram, rom);

    REQUIRE(&bus.get_ram() == &ram);
    REQUIRE(&bus.get_rom() == &rom);
}

TEST_CASE("MemoryBus preserves data isolation between ROM and RAM", "[memory]")
{
    std::vector<uint8_t> romdata = {0xA1, 0xB2, 0xC3, 0xD4};
    ROM rom(4096);
    rom.load(romdata);

    RAM ram(128);
    MemoryBus bus(ram, rom);

    bus.write(0x1000, 0xEE);
    REQUIRE(bus.read(0x0000) == 0xA1);
    REQUIRE(bus.read(0x1000) == 0xEE);
}
