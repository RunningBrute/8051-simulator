module;

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

export module assembler.parser;

import logger;

export enum class ParsedType
{
    NOP,
    INC_A,
    ADD_A_IMM,
    ADDC_A_IMM,
    MOV_A_IMM,
    MOV_DIRECT_A,
    MOV_A_DIRECT,
    SJMP
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
    ParsedInstruction parse(std::vector<std::string>& t, size_t line)
    {
        if (t.empty())
        {
            throw std::runtime_error("Empty line");
        }

        // NOP
        if (t[0] == "NOP")
        {
            AppLogger::debug("parse NOP");
            return {ParsedType::NOP, 0, line};
        }

        // INC A
        if (t[0] == "INC" && t.size() == 2 && t[1] == "A")
        {
            AppLogger::debug("parse INC_A");
            return {ParsedType::INC_A, 0, line};
        }

        // ADD A,#imm
        if (t[0] == "ADD" && t.size() == 3 && t[1] == "A" && t[2][0] == '#')
        {
            AppLogger::debug("parse ADDC_IMM_A");
            return {ParsedType::ADD_A_IMM, parse_number(t[2].substr(1)), line};
        }

        // ADDC A,#imm
        if (t[0] == "ADDC" && t.size() == 3 && t[1] == "A" && t[2][0] == '#')
        {
            AppLogger::debug("parse ADDC_A_IMM");
            return {ParsedType::ADDC_A_IMM, parse_number(t[2].substr(1)), line};
        }

        // MOV A,#imm
        if (t[0] == "MOV" && t.size() == 3 && t[1] == "A" && t[2][0] == '#')
        {
            AppLogger::debug("parse MOV_A_IMM");
            return {ParsedType::MOV_A_IMM, parse_number(t[2].substr(1)), line};
        }

        // MOV direct,A
        if (t[0] == "MOV" && t.size() == 4 && t[2] == "," && t[3] == "A")
        {
            AppLogger::debug("parse MOV_DIRECT_A");
            return {ParsedType::MOV_DIRECT_A, parse_number(t[1]), line};
        }

        // MOV A,direct
        if (t[0] == "MOV" && t.size() == 4 && t[1] == "A" && t[2] == ",")
        {
            AppLogger::debug("parse MOV_A_DIRECT");
            return {ParsedType::MOV_A_DIRECT, parse_number(t[3]), line};
        }

        //SJMP
        if (t[0] == "SJMP" && t.size() == 2 && t[1] == "$")
        {
            AppLogger::debug("parse SJMP");
            return {ParsedType::SJMP, 0, line};
        }

        throw std::runtime_error("Unknown instruction at line " + std::to_string(line));
    }

private:
    static uint16_t parse_number(std::string s)
    {
        // Remove whitespace
        while (!s.empty() && isspace(s.front())) s.erase(s.begin());
        while (!s.empty() && isspace(s.back()))  s.pop_back();

        // Remove prefix '#'
        if (!s.empty() && s[0] == '#')
            s.erase(s.begin());

        // HEX: 0xNN
        if (s.size() > 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
        {
            return std::stoi(s, nullptr, 16);
        }

        // HEX: NN h
        if (!s.empty() && (s.back() == 'h' || s.back() == 'H'))
        {
            s.pop_back();
            return std::stoi(s, nullptr, 16);
        }

        // BIN: 0bxxxx
        if (s.size() > 2 && s[0] == '0' && (s[1] == 'b' || s[1] == 'B'))
        {
            s.erase(0, 2);
            return std::stoi(s, nullptr, 2);
        }

        // DEC fallback
        if (s.empty() || (!isdigit(s[0]) && s[0] != '-' && s[0] != '+'))
        {
            throw std::runtime_error("parse_number: not a number: '" + s + "'");
        }

        return std::stoi(s, nullptr, 10);
    }
};
