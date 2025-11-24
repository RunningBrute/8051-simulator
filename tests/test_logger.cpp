#include <catch2/catch_all.hpp>

#include <filesystem>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

import logger;

TEST_CASE("Logger logs", "[logger]")
{
    std::filesystem::create_directory("logs");
    FileSink::init("logs/test.log");
    AppLogger::start();

    AppLogger::info("test message");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    AppLogger::stop();

    std::ifstream f("logs/test.log");
    REQUIRE(f.good());

    std::string line;
    std::getline(f, line);

    REQUIRE(line.find("test message") != std::string::npos);
}

