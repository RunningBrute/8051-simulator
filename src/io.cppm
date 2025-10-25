#include <array>
#include <cstdint>

export module io;

export class IO
{
public:
    IO();
    void write_port(uint8_t port, uint8_t value);
    uint8_t read_port(uint8_t port) const;
private:
    std::array<uint8_t, 4> ports;
};

module :private;

IO::IO()
{
    ports.fill(0);
}

void IO::write_port(uint8_t port, uint8_t value)
{
    if (port < ports.size()) ports[port] = value;
}

uint8_t IO::read_port(uint8_t port) const
{
    return (port < ports.size()) ? ports[port] : 0xFF;
}