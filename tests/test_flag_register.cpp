#include <catch2/catch_test_macros.hpp>
#include <sstream> // required for std::ostringstream
#include <iostream>

import registers;

TEST_CASE("FlagRegister initializes correctly", "[flag_register]")
{
    FlagRegister psw("PSW");
    REQUIRE(std::string(psw.get_name()) == "PSW");
    REQUIRE(psw.read() == 0);
    REQUIRE_FALSE(psw.carry());
    REQUIRE_FALSE(psw.aux_carry());
    REQUIRE_FALSE(psw.overflow());
}

TEST_CASE("FlagRegister sets and clears carry flag", "[flag_register]")
{
    FlagRegister psw("PSW");
    psw.set_carry(true);
    REQUIRE(psw.carry());
    REQUIRE((psw.read() & (1 << 7)) != 0);

    psw.set_carry(false);
    REQUIRE_FALSE(psw.carry());
    REQUIRE((psw.read() & (1 << 7)) == 0);
}

TEST_CASE("FlagRegister sets and clears auxiliary carry flag", "[flag_register]")
{
    FlagRegister psw("PSW");
    psw.set_aux_carry(true);
    REQUIRE(psw.aux_carry());
    REQUIRE((psw.read() & (1 << 6)) != 0);

    psw.set_aux_carry(false);
    REQUIRE_FALSE(psw.aux_carry());
    REQUIRE((psw.read() & (1 << 6)) == 0);
}

TEST_CASE("FlagRegister sets and clears overflow flag", "[flag_register]")
{
    FlagRegister psw("PSW");
    psw.set_overflow(true);
    REQUIRE(psw.overflow());
    REQUIRE((psw.read() & (1 << 2)) != 0);

    psw.set_overflow(false);
    REQUIRE_FALSE(psw.overflow());
    REQUIRE((psw.read() & (1 << 2)) == 0);
}

TEST_CASE("FlagRegister allows direct write and read of value", "[flag_register]")
{
    FlagRegister psw("PSW");
    psw.write(0b11100100); // 0xE4
    REQUIRE(psw.read() == 0xE4);

    REQUIRE(psw.carry());
    REQUIRE(psw.aux_carry());
    REQUIRE(psw.overflow());
}

TEST_CASE("FlagRegister keeps correct name", "[flag_register]")
{
    FlagRegister f1("PSW1");
    FlagRegister f2("FLAGS", 0xFF);
    REQUIRE(std::string(f1.get_name()) == "PSW1");
    REQUIRE(std::string(f2.get_name()) == "FLAGS");
    REQUIRE(f2.read() == 0xFF);
}

TEST_CASE("FlagRegister parity bit can be set and read", "[flag_register]")
{
    FlagRegister psw("PSW");
    psw.set_parity(true);
    REQUIRE(psw.parity());
    psw.set_parity(false);
    REQUIRE_FALSE(psw.parity());
}

TEST_CASE("FlagRegister ostream output includes all flags", "[flag_register]")
{
    FlagRegister psw("PSW");
    psw.set_carry(true);
    psw.set_aux_carry(true);
    psw.set_overflow(true);
    psw.set_parity(true);

    std::ostringstream oss;
    oss << psw;
    std::string out = oss.str();

    REQUIRE(out.find("CY=1") != std::string::npos);
    REQUIRE(out.find("AC=1") != std::string::npos);
    REQUIRE(out.find("OV=1") != std::string::npos);
    REQUIRE(out.find("P=1") != std::string::npos);
}
