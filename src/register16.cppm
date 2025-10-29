#include <cstdint>;
#include <string>;

export module register16;

export class Register16
{
public:
    Register16(std::string name, uint16_t initial_value = 0) 
        : name(std::move(name)),
          value(initial_value) {}

    void write(uint16_t v) { value = v; }
    uint16_t read() const { return value; }

    uint8_t high() const { return static_cast<uint8_t>(value >> 8); }
    uint8_t low() const { return static_cast<uint8_t>(value & 0xFF); }

    const std::string& get_name() const { return name; }

private:
    std::string name;
    uint16_t value;
};