#include <catch2/catch_test_macros.hpp>

import assembler.tokenizer;

TEST_CASE("Tokenizer splits MOV A,#25 correctly")
{
    Tokenizer t;

    auto tokens = t.tokenize("MOV A, #25");

    REQUIRE(tokens.size() == 4);
    REQUIRE(tokens[0] == "MOV");
    REQUIRE(tokens[1] == "A");
    REQUIRE(tokens[2] == ",");
    REQUIRE(tokens[3] == "#25");
}

TEST_CASE("Tokenizer strips comments")
{
    Tokenizer t;
    auto tokens = t.tokenize("MOV A,#10 ; comment here");

    REQUIRE(tokens.size() == 3);
    REQUIRE(tokens[0] == "MOV");
    REQUIRE(tokens[1] == "A");
    REQUIRE(tokens[2] == "#10");
}

TEST_CASE("Tokenizer handles direct addresses")
{
    Tokenizer t;
    auto tokens = t.tokenize("MOV 0x20, A");

    REQUIRE(tokens[0] == "MOV");
    REQUIRE(tokens[1] == "0x20");
    REQUIRE(tokens[2] == ",");
    REQUIRE(tokens[3] == "A");
}
