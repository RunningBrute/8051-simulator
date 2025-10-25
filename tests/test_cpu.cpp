#include <catch2/catch_test_macros.hpp>

import cpu;

TEST_CASE("CPU reset clears registers")
{
    CPU cpu;
    cpu.reset();
    REQUIRE(cpu.get_register("A") == 0);
}