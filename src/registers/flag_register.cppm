#include <cstdlib>
#include <string>

export module registers.flag_register;

export class FlagRegister
{
public:
    FlagRegister(std::string name, uint8_t initial_value = 0)
        : name(std::move(name)),
          value(initial_value)
    {}

    void set_carry(bool v) { set_bit(7, v); }
    bool carry() const { return test_bit(7); }

    void set_overflow(bool v) { set_bit(2, v); }
    bool overflow() const { return test_bit(2); }

    void set_aux_carry(bool v) { set_bit(6, v); }
    bool aux_carry() const { return test_bit(6); }

    uint8_t read() const { return value; }
    void write(uint8_t v) { value = v; }

    const std::string& get_name() const { return name; }

private:
    std::string name;
    uint8_t value = 0;

    void set_bit(uint8_t bit, bool v) {
        if (v) value |= (1 << bit);
        else value &= ~(1 << bit);
    }
    bool test_bit(uint8_t bit) const { return (value >> bit) & 1; }
};