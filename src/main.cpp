#include <iostream>

import assembler;
import system;
import logger;

int main(int argc, char** argv)
{
    FileSink::init("app.log");
    AppLogger::start();

    if (argc < 2)
    {
        AppLogger::info("Usage: f.e. 8051-simulator.exe example/mov_test.asm");
        return 1;
    }

    try
    {
        Assembler assembler;
        System system;

        auto program = assembler.assemble_file(argv[1]);
        system.load_program(program);
        system.reset();

        AppLogger::info("8051 Simulator started");
        for (;;)
        {
            system.cpu.step();
        }
    }
    catch (const std::exception& e)
    {
        std::string msg = std::string("[EXCEPTION] std::exception: ") + e.what();
        AppLogger::error(msg);
        return 2;
    }
    catch (...)
    {
        AppLogger::error("[EXCEPTION] unknown exception ");
        return 3;
    }

    return 0;
}