#include <catch2/catch_test_macros.hpp>

import registers;

TEST_CASE("Register8 stores and retrieves values", "[register8]")
{
    Register8 reg{"A"};
    reg.write(0x55);
    REQUIRE(reg.read() == 0x55);

    reg.write(0xAA);
    REQUIRE(reg.read() == 0xAA);
}

TEST_CASE("Register8 has independent state", "[register8]")
{
    Register8 r1{"A"}, r2{"B"};
    r1.write(0x11);
    r2.write(0x22);

    REQUIRE(r1.read() == 0x11);
    REQUIRE(r2.read() == 0x22);
    REQUIRE(r1.read() != r2.read());
}

TEST_CASE("Register8 supports copy semantics", "[register8]")
{
    Register8 r1{"A"};
    r1.write(0x77);
    Register8 r2 = r1;
    REQUIRE(r2.read() == 0x77);
}

TEST_CASE("Register8 correctly sets, clears and tests bits", "[register8]")
{
    Register8 reg{"ACC"};
    reg.write(0x00);

    reg.set_bit(3);
    REQUIRE(reg.test_bit(3));

    reg.clear_bit(3);
    REQUIRE_FALSE(reg.test_bit(3));

    // Ensure other bits are untouched
    reg.write(0xF0);
    reg.clear_bit(0);
    REQUIRE(reg.read() == 0xF0);
}

TEST_CASE("Register8 get_name returns correct identifier", "[register8]")
{
    Register8 reg{"ACC"};
    REQUIRE(std::string(reg.get_name()) == "ACC");
}
