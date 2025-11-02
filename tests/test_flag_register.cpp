#include <catch2/catch_test_macros.hpp>

import registers.flag_register;

TEST_CASE("FlagRegister initializes correctly", "[flag_register]") {
    FlagRegister psw("PSW");
    REQUIRE(psw.get_name() == "PSW");
    REQUIRE(psw.read() == 0);
    REQUIRE_FALSE(psw.carry());
    REQUIRE_FALSE(psw.aux_carry());
    REQUIRE_FALSE(psw.overflow());
}

TEST_CASE("FlagRegister sets and clears carry flag", "[flag_register]") {
    FlagRegister psw("PSW");
    psw.set_carry(true);
    REQUIRE(psw.carry());
    REQUIRE((psw.read() & (1 << 7)) != 0);

    psw.set_carry(false);
    REQUIRE_FALSE(psw.carry());
    REQUIRE((psw.read() & (1 << 7)) == 0);
}

TEST_CASE("FlagRegister sets and clears auxiliary carry flag", "[flag_register]") {
    FlagRegister psw("PSW");
    psw.set_aux_carry(true);
    REQUIRE(psw.aux_carry());
    REQUIRE((psw.read() & (1 << 6)) != 0);

    psw.set_aux_carry(false);
    REQUIRE_FALSE(psw.aux_carry());
    REQUIRE((psw.read() & (1 << 6)) == 0);
}

TEST_CASE("FlagRegister sets and clears overflow flag", "[flag_register]") {
    FlagRegister psw("PSW");
    psw.set_overflow(true);
    REQUIRE(psw.overflow());
    REQUIRE((psw.read() & (1 << 2)) != 0);

    psw.set_overflow(false);
    REQUIRE_FALSE(psw.overflow());
    REQUIRE((psw.read() & (1 << 2)) == 0);
}

TEST_CASE("FlagRegister allows direct write and read of value", "[flag_register]") {
    FlagRegister psw("PSW");
    psw.write(0b11100100); // 0xE4
    REQUIRE(psw.read() == 0xE4);

    REQUIRE(psw.carry());
    REQUIRE(psw.aux_carry());
    REQUIRE(psw.overflow());
}

TEST_CASE("FlagRegister keeps correct name", "[flag_register]") {
    FlagRegister f1("PSW1");
    FlagRegister f2("FLAGS", 0xFF);
    REQUIRE(f1.get_name() == "PSW1");
    REQUIRE(f2.get_name() == "FLAGS");
    REQUIRE(f2.read() == 0xFF);
}
