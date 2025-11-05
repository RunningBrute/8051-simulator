#include <catch2/catch_test_macros.hpp>

import registers;

TEST_CASE("Register16 stores and retrieves 16-bit values", "[register16]")
{
    Register16 reg{"DPTR"};
    reg.write(0xABCD);
    REQUIRE(reg.read() == 0xABCD);
}

TEST_CASE("Register16 correctly extracts high and low bytes", "[register16]")
{
    Register16 reg{"PC"};
    reg.write(0x1234);
    REQUIRE(reg.high() == 0x12);
    REQUIRE(reg.low() == 0x34);
}

TEST_CASE("Register16 get_name returns correct identifier", "[register16]") 
{
    Register16 reg{"DPTR"};
    REQUIRE(std::string(reg.get_name()) == "DPTR");
}

TEST_CASE("Register16 preserves independent state", "[register16]")
{
    Register16 r1{"D1"};
    Register16 r2{"D2"};
    r1.write(0xAAAA);
    r2.write(0x5555);

    REQUIRE(r1.read() == 0xAAAA);
    REQUIRE(r2.read() == 0x5555);
    REQUIRE(r1.read() != r2.read());
}
