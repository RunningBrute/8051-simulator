module;
#include <cstdint>
#include <string>
#include <iostream>

export module registers;

export class Register8
{
public:
    explicit Register8(std::string name, uint8_t initial_value = 0)
        : name(std::move(name)), value(initial_value)
    {}

    void write(uint8_t val) noexcept { value = val; }
    [[nodiscard]] uint8_t read() const noexcept { return value; }

    void set_bit(uint8_t bit) { value |= (1 << bit); }
    void clear_bit(uint8_t bit) { value &= ~(1 << bit); }
    bool test_bit(uint8_t bit) const { return (value >> bit) & 1; }

    void reset() { value = 0; }

    const std::string_view get_name() const noexcept { return name; }

    friend std::ostream& operator<<(std::ostream& os, const Register8& r)
    {
        os << r.name << " = 0x" << std::hex << static_cast<int>(r.value);
        return os;
    }

private:
    std::string name;
    uint8_t value;
};

export class Register16
{
public:
    explicit Register16(std::string name, uint16_t initial_value = 0) 
        : name(std::move(name)), value(initial_value)
    {}

    void write(uint16_t v) { value = v; }
    [[nodiscard]] uint16_t read() const noexcept { return value; }

    [[nodiscard]] uint8_t high() const noexcept { return static_cast<uint8_t>(value >> 8); }
    [[nodiscard]] uint8_t low() const noexcept { return static_cast<uint8_t>(value & 0xFF); }

    void reset() { value = 0; }

    const std::string_view get_name() const noexcept { return name; }

    friend std::ostream& operator<<(std::ostream& os, const Register16& r)
    {
        os << r.name << " = 0x" << std::hex << r.value;
        return os;
    }

private:
    std::string name;
    uint16_t value;
};

export class FlagRegister
{
public:
    explicit FlagRegister(std::string name, std::uint8_t initial_value = 0)
        : name(std::move(name)), value(initial_value) {}

    void set_carry(bool v) { set_bit(7, v); }
    [[nodiscard]] bool carry() const noexcept { return test_bit(7); }

    void set_overflow(bool v) { set_bit(2, v); }
    [[nodiscard]] bool overflow() const noexcept { return test_bit(2); }

    void set_aux_carry(bool v) { set_bit(6, v); }
    [[nodiscard]] bool aux_carry() const noexcept { return test_bit(6); }

    [[nodiscard]] std::uint8_t read() const noexcept { return value; }
    void write(std::uint8_t v) { value = v; }

    void set_parity(bool v) { set_bit(0, v); }
    [[nodiscard]] bool parity() const noexcept { return test_bit(0); }

    void reset() { value = 0; }

    const std::string_view get_name() const noexcept { return name; }

    friend std::ostream& operator<<(std::ostream& os, const FlagRegister& f)
    {
        os << f.name << " ["
           << "CY=" << f.carry()
           << " AC=" << f.aux_carry()
           << " OV=" << f.overflow()
           << " P=" << f.parity()
           << "]";
        return os;
    }

private:
    std::string name;
    std::uint8_t value = 0;

    void set_bit(std::uint8_t bit, bool v) {
        if (v) value |= (1 << bit);
        else value &= ~(1 << bit);
    }
    [[nodiscard]] bool test_bit(std::uint8_t bit) const noexcept { return (value >> bit) & 1; }
};