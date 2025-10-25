#include <vector>
#include <cstdint>

export module memory;

export class Memory
{
public:
    explicit Memory(std::size_t size = 256);
    uint8_t read(uint16_t address) const;
    void write(uint16_t address, uint8_t value);
private:
    std::vector<uint8_t> data;
};

module :private;

Memory::Memory(std::size_t size) : data(size, 0) {}

uint8_t Memory::read(uint16_t address) const
{
    return (address < data.size()) ? data[address] : 0xFF;
}

void Memory::write(uint16_t address, uint8_t value)
{
    if (address < data.size()) data[address] = value;
}