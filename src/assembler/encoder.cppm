module;

#include <vector>
#include <stdexcept>

export module assembler.encoder;

import assembler.parser;

export class Encoder
{
public:
    std::vector<uint8_t> encode(const ParsedInstruction& p)
    {
        switch (p.type) {
            case ParsedType::NOP:
                return {0x00};

            case ParsedType::INC_A:
                return {0x04};

            case ParsedType::ADD_A_IMM:
                return {0x24, static_cast<uint8_t>(p.operand)};

            case ParsedType::ADDC_A_IMM:
                return {0x34, static_cast<uint8_t>(p.operand)};

            case ParsedType::MOV_A_IMM:
                return {0x74, static_cast<uint8_t>(p.operand)};

            case ParsedType::MOV_DIRECT_A:
                return {0xF5, static_cast<uint8_t>(p.operand)};

            case ParsedType::MOV_A_DIRECT:
                return {0xE5, static_cast<uint8_t>(p.operand)};
        }

        throw std::runtime_error("Unknown parsed type");
    }
};
