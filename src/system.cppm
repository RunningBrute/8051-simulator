module;
#include <span>
#include <cstdint>
#include <string>
#include <vector>
#include <sstream>

export module system;

import cpu;
import memory;
import memory.bus;
import io;
import logger;

export class System
{
public:
    System()
        : ram(128), rom(4096),
          bus(ram, rom),
          cpu(bus)
    {
        AppLogger::info("System started.");
    }

    void reset()
    {
        cpu.reset();
        ram = RAM(128);
        rom = ROM(4096);
        AppLogger::info("System reset.");
    }

    void load_program(const std::vector<uint8_t>& program)
    {
        rom.load(program);
        AppLogger::info("Program loaded into ROM memory.");
        print_programm(program);
    }

    void print_programm(const std::vector<uint8_t>& program)
    {   
        std::ostringstream oss;
        for (std::size_t i = 0; i < program.size(); i++)
        {
            oss << std::uppercase << std::hex << static_cast<int>(program[i]);
        }
        AppLogger::debug("Line to parse: " + oss.str());
    }

    RAM ram;
    ROM rom;
    IO io;
    MemoryBus bus;
    CPU cpu;
};