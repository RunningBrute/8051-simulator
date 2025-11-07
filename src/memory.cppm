module;
#include <vector>
#include <cstdint>
#include <algorithm>

export module memory;

export template<bool ReadOnly>
class Memory
{
public:
    explicit Memory(std::size_t size)
        : storage(size, 0) 
    {}
    
    [[nodiscard]] uint8_t read(uint16_t address) const noexcept
    {
        return (address < storage.size()) ? storage[address] : 0xFF;
    }

    // RAM can use write method
    void write(uint16_t address, uint8_t value) requires (!ReadOnly)
    {
        if (address < storage.size()) storage[address] = value;
    }

    // from ROM we can only read, so write is deleted
    void write(uint16_t, uint8_t) requires (ReadOnly) = delete;

    [[nodiscard]] std::size_t size() const noexcept
    { 
        return storage.size();
    }

    uint8_t* data() noexcept
    {
        return storage.data();
    }

    const uint8_t* data() const noexcept
    {
        return storage.data();
    }

    void load(const std::vector<uint8_t>& data) requires (ReadOnly)
    {
        std::copy_n(data.begin(), std::min(data.size(), storage.size()), storage.begin());
    }

private:
    std::vector<uint8_t> storage;
};

export using RAM = Memory<false>;
export using ROM = Memory<true>;