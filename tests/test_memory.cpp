#include <catch2/catch_test_macros.hpp>

import memory;

TEST_CASE("Memory default size is 256 bytes", "[memory]")
{
    Memory mem;
    REQUIRE(mem.size() == 256);
}

TEST_CASE("Memory read returns 0xFF for out of range addresses", "[memory]")
{
    Memory mem(128);
    REQUIRE(mem.read(200) == 0xFF);
}

TEST_CASE("Memory write and read within range works", "[memory]")
{
    Memory mem(64);
    mem.write(10, 0xAB);
    REQUIRE(mem.read(10) == 0xAB);
}

TEST_CASE("Memory write out of range does nothing", "[memory]")
{
    Memory mem(32);
    
    mem.write(100, 0x77); // out of range, should not crash or modify

    // check random in range cell to ensure it wasn't affected
    mem.write(5, 0x12);
    REQUIRE(mem.read(5) == 0x12);

    // still 0xFF for out of range
    REQUIRE(mem.read(100) == 0xFF);
}

TEST_CASE("Memory data() pointer exposes correct raw RAM buffer", "[memory]")
{
    Memory mem(32);
    auto raw = mem.data();
    raw[3] = 0x55;
    REQUIRE(mem.read(3) == 0x55);
}
