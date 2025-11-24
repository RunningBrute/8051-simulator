#include <iostream>
#include <filesystem>

import assembler;
import system;
import logger;

int main(int argc, char** argv)
{
    std::filesystem::create_directory("logs");
    FileSink::init("logs/app.log");
    AppLogger::start();

    if (argc < 2)
    {
        AppLogger::info("Usage: f.e. 8051-simulator.exe example/mov_test.asm");
        AppLogger::stop();
        return 1;
    }

    try
    {
        AppLogger::info("8051 Simulator started");

        Assembler assembler;
        System system;

        auto program = assembler.assemble_file(argv[1]);
        system.reset();
        system.load_program(program);

        for (;;)
        {
            system.cpu.step();
        }
    }
    catch (const std::exception& e)
    {
        std::string msg = std::string("[EXCEPTION] std::exception: ") + e.what();
        AppLogger::error(msg);
        AppLogger::stop();
        return 2;
    }
    catch (...)
    {
        AppLogger::error("[EXCEPTION] unknown exception ");
        AppLogger::stop();
        return 3;
    }

    AppLogger::stop();
    return 0;
}