module;
#include <vector>
#include <cstdint>

export module memory;

export class Memory
{
public:
    explicit Memory(std::size_t size = 256);
    uint8_t read(uint16_t address) const;
    void write(uint16_t address, uint8_t value);

    uint8_t* data() { return memory.data(); }
    const uint8_t* data() const { return memory.data(); }
    std::size_t size() const { return memory.size(); }
private:
    std::vector<uint8_t> memory;
};

module :private;

Memory::Memory(std::size_t size) 
    : memory(size, 0)
{}

uint8_t Memory::read(uint16_t address) const
{
    return (address < memory.size()) ? memory[address] : 0xFF;
}

void Memory::write(uint16_t address, uint8_t value)
{
    if (address < memory.size())
        memory[address] = value;
}