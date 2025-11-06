#include <catch2/catch_test_macros.hpp>
#include <vector>
import memory;

TEST_CASE("ROM initializes to zero-filled memory", "[memory][rom]")
{
    ROM rom(128);
    for (size_t i = 0; i < rom.size(); ++i)
        REQUIRE(rom.read(i) == 0x00);
}

TEST_CASE("ROM returns 0xFF for out-of-range reads", "[memory][rom]")
{
    ROM rom(64);
    REQUIRE(rom.read(0x200) == 0xFF);
}

TEST_CASE("ROM can load data vector on construction or load()", "[memory][rom]")
{
    std::vector<uint8_t> prog = {0x11, 0x22, 0x33, 0x44};
    ROM rom(8);
    rom.load(prog);

    REQUIRE(rom.read(0) == 0x11);
    REQUIRE(rom.read(1) == 0x22);
    REQUIRE(rom.read(3) == 0x44);
    REQUIRE(rom.read(4) == 0x00); // beyond vector size, still 0
}
