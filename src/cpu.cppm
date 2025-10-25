#include <array>
#include <string>
#include <cstdint>
#include <iostream>

export module cpu;

export class CPU
{
public:
    CPU();
    void reset();
    uint8_t get_register(const std::string& name) const;
private:
    std::array<uint8_t, 8> registers;
};

module :private;

CPU::CPU()
{
    reset();
}

void CPU::reset()
{
    registers.fill(0);
}

uint8_t CPU::get_register(const std::string& name) const
{
    if (name == "A") return registers[0];
    return 0;
}