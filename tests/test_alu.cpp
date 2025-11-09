#include <catch2/catch_test_macros.hpp>
import registers;
import alu;

TEST_CASE("ALU performs ADD and sets flags")
{
    FlagRegister psw("PSW");
    ALU alu(psw);

    uint8_t res = alu.execute(ALUOperation::ADD, 0x7F, 0x01);
    REQUIRE(res == 0x80);
    REQUIRE(psw.overflow());
    REQUIRE_FALSE(psw.carry());
}