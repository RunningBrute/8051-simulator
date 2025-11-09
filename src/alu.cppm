module;
#include <cstdint>
#include <iostream>
#include <bit>

export module alu;

import registers;

export enum class ALUOperation
{
    ADD, ADDC, SUBB,
    INC, DEC,
    ANL, ORL, XRL,
    CPL
};

export class ALU
{
public:
    explicit ALU(FlagRegister& flags)
        : flags(flags)
    {}

    uint8_t execute(ALUOperation op, uint8_t acc, uint8_t operand);

private:
    FlagRegister& flags;

    void update_flags_add(uint8_t a, uint8_t b, uint16_t result);
    void update_flags_sub(uint8_t a, uint8_t b, uint16_t result);
    void update_parity(uint8_t value);
};

module :private;

uint8_t ALU::execute(ALUOperation op, uint8_t acc, uint8_t operand)
{
    uint16_t result = 0;
    switch (op) {
        case ALUOperation::ADD:
            result = acc + operand;
            update_flags_add(acc, operand, result);
            break;

        case ALUOperation::ADDC:
            result = acc + operand + (flags.carry() ? 1 : 0);
            update_flags_add(acc, operand, result);
            break;

        case ALUOperation::SUBB:
            result = acc - operand - (flags.carry() ? 1 : 0);
            update_flags_sub(acc, operand, result);
            break;

        case ALUOperation::INC:
            result = (acc + 1) & 0xFF;
            update_parity(result);
            break;

        case ALUOperation::DEC:
            result = (acc - 1) & 0xFF;
            update_parity(result);
            break;

        case ALUOperation::ANL:
            result = acc & operand;
            update_parity(result);
            break;

        case ALUOperation::ORL:
            result = acc | operand;
            update_parity(result);
            break;

        case ALUOperation::XRL:
            result = acc ^ operand;
            update_parity(result);
            break;

        case ALUOperation::CPL:
            result = ~acc & 0xFF;
            update_parity(result);
            break;
    }

    return static_cast<uint8_t>(result);
}

void ALU::update_flags_add(uint8_t a, uint8_t b, uint16_t result)
{
    flags.set_carry(result > 0xFF);
    flags.set_aux_carry(((a & 0x0F) + (b & 0x0F)) > 0x0F);
    flags.set_overflow(((a ^ b ^ 0x80) & (a ^ result) & 0x80) != 0);

    update_parity(static_cast<uint8_t>(result));
}

void ALU::update_flags_sub(uint8_t a, uint8_t b, uint16_t result)
{
    flags.set_carry(result > 0xFF);
    flags.set_aux_carry(((a & 0x0F) - (b & 0x0F)) < 0);
    flags.set_overflow(((a ^ b) & (a ^ result) & 0x80) != 0);

    update_parity(static_cast<uint8_t>(result));
}

void ALU::update_parity(uint8_t value)
{
    flags.set_parity(std::popcount(value) % 2 == 0);
}
