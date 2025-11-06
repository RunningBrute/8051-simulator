#include <catch2/catch_test_macros.hpp>
import memory;

TEST_CASE("RAM supports write and read operations", "[memory][ram]")
{
    RAM ram(128);
    ram.write(0x00, 0xAA);
    ram.write(0x7F, 0x55);

    REQUIRE(ram.read(0x00) == 0xAA);
    REQUIRE(ram.read(0x7F) == 0x55);
}

TEST_CASE("RAM overwrites existing values", "[memory][ram]")
{
    RAM ram(64);
    ram.write(10, 0x11);
    ram.write(10, 0x22);
    REQUIRE(ram.read(10) == 0x22);
}

TEST_CASE("RAM ignores out-of-range writes gracefully", "[memory][ram]")
{
    RAM ram(64);
    REQUIRE_NOTHROW(ram.write(200, 0x42));
    REQUIRE(ram.read(200) == 0xFF);
}

TEST_CASE("RAM exposes mutable data() pointer", "[memory][ram]")
{
    RAM ram(32);
    uint8_t* ptr = ram.data();
    REQUIRE(ptr != nullptr);

    ptr[3] = 0x77;
    REQUIRE(ram.read(3) == 0x77);
}

TEST_CASE("RAM contents persist through multiple reads", "[memory][ram]")
{
    RAM ram(8);
    ram.write(1, 0x12);
    ram.write(2, 0x34);
    REQUIRE(ram.read(1) == 0x12);
    REQUIRE(ram.read(2) == 0x34);
}
