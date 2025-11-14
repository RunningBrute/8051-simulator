module;

#include <string>
#include <vector>
#include <stdexcept>

export module assembler.parser;

export enum class ParsedType
{
    NOP,
    INC_A,
    ADD_A_IMM,
    ADDC_A_IMM,
    MOV_A_IMM,
    MOV_DIRECT_A,
    MOV_A_DIRECT
};

export struct ParsedInstruction
{
    ParsedType type;
    uint16_t operand;
    size_t line;
};

export class Parser
{
public:
    ParsedInstruction parse(const std::vector<std::string>& t, size_t line)
    {
        if (t.empty())
            throw std::runtime_error("Empty line");

        // NOP
        if (t[0] == "NOP")
        {
            return {ParsedType::NOP, 0, line};
        }

        // INC A
        if (t[0] == "INC" && t.size() == 2 && t[1] == "A")
        {
            return {ParsedType::INC_A, 0, line};
        }

        // ADD A,#imm
        if (t[0] == "ADD" && t.size() == 3 && t[1] == "A" && t[2][0] == '#')
        {
            return {ParsedType::ADD_A_IMM, parse_number(t[2].substr(1)), line};
        }

        // ADDC A,#imm
        if (t[0] == "ADDC" && t.size() == 3 && t[1] == "A" && t[2][0] == '#')
        {
            return {ParsedType::ADDC_A_IMM, parse_number(t[2].substr(1)), line};
        }

        // MOV A,#imm
        if (t[0] == "MOV" && t.size() == 3 && t[1] == "A" && t[2][0] == '#')
        {
            return {ParsedType::MOV_A_IMM, parse_number(t[2].substr(1)), line};
        }

        // MOV direct,A
        if (t[0] == "MOV" && t.size() == 4 && t[2] == "," && t[3] == "A")
        {
            return {ParsedType::MOV_DIRECT_A, parse_number(t[1]), line};
        }

        // MOV A,direct
        if (t[0] == "MOV" && t.size() == 4 && t[1] == "A" && t[2] == ",")
        {
            return {ParsedType::MOV_A_DIRECT, parse_number(t[3]), line};
        }

        throw std::runtime_error("Unknown instruction at line " + std::to_string(line));
    }

private:
    static uint16_t parse_number(const std::string& s)
    {
        if (s.starts_with("0x") || s.starts_with("0X"))
            return std::stoi(s, nullptr, 16);
        return std::stoi(s);
    }
};
