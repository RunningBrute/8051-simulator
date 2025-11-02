#include <cstdint>
#include <string>

export module registers.register8;

export class Register8
{
public:
    Register8(std::string name, uint8_t initial_value = 0)
        : name(std::move(name)),
          value(initial_value)
    {}

    void write(uint8_t val) { value = val; }
    uint8_t read() const { return value; }

    void set_bit(uint8_t bit) { value |= (1 << bit); }
    void clear_bit(uint8_t bit) { value &= ~(1 << bit); }
    bool test_bit(uint8_t bit) const { return (value >> bit) & 1; }

    const std::string& get_name() const { return name; }

private:
    std::string name;
    uint8_t value;
};