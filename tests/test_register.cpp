#include <catch2/catch_test_macros.hpp>

import register8;
import register16;

TEST_CASE("Register stores and retrieves values", "[register]") {
    Register reg{"A"};
    reg.write(0x55);
    REQUIRE(reg.read() == 0x55);

    reg.write(0xAA);
    REQUIRE(reg.read() == 0xAA);
}

TEST_CASE("Register has independent state", "[register]") {
    Register r1{"A"}, r2{"B"};
    r1.write(0x11);
    r2.write(0x22);

    REQUIRE(r1.read() == 0x11);
    REQUIRE(r2.read() == 0x22);
    REQUIRE(r1.read() != r2.read());
}

TEST_CASE("Register supports copy semantics", "[register]") {
    Register r1{"A"};
    r1.write(0x77);
    Register r2 = r1;
    REQUIRE(r2.read() == 0x77);
}

TEST_CASE("Register16 stores and retrieves 16-bit values", "[register16]") {
    Register16 reg{"DPTR"};
    reg.write(0xABCD);
    REQUIRE(reg.read() == 0xABCD);
}

TEST_CASE("Register16 correctly extracts high and low bytes", "[register16]") {
    Register16 reg{"PC"};
    reg.write(0x1234);
    REQUIRE(reg.high() == 0x12);
    REQUIRE(reg.low() == 0x34);
}