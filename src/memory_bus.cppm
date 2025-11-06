module;
#include <cstdint>
#include <stdexcept>

export module memory.bus;

import memory;

export class MemoryBus
{
public:
    MemoryBus(RAM& ram, ROM& rom)
        : ram(ram), rom(rom)
    {}

    [[nodiscard]] uint8_t read(uint16_t address) const noexcept
    {
        if (address < 0x1000)
            return rom.read(address);
        else if (address < 0x1080)
            return ram.read(address - 0x1000);
        return 0xFF;
    }

    void write(uint16_t address, uint8_t value)
    {
        if (address < 0x1000)
            throw std::runtime_error("Write to ROM address space");

        // RAM: 0x1000 – 0x107F
        else if (address < 0x1080)
            ram.write(address - 0x1000, value);
    }

    [[nodiscard]] RAM& get_ram() noexcept{ return ram; }
    [[nodiscard]] const RAM& get_ram() const noexcept { return ram; }

    [[nodiscard]] ROM& get_rom() noexcept { return rom; }
    [[nodiscard]] const ROM& get_rom() const noexcept { return rom; }

private:
    RAM& ram;
    ROM& rom;
};
