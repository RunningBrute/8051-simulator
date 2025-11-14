module;

#include <fstream>
#include <sstream>
#include <vector>

export module assembler;

import assembler.tokenizer;
import assembler.parser;
import assembler.encoder;

export class Assembler
{
public:
    std::vector<std::uint8_t> assemble_file(const std::string& path)
    {
        std::ifstream f(path);
        if (!f)
            throw std::runtime_error("Cannot open file: " + path);

        Tokenizer tokenizer;
        Parser parser;
        Encoder encoder;

        std::vector<std::uint8_t> program;

        std::string line;
        std::size_t line_no = 1;

        while (std::getline(f, line))
        {
            auto tokens = tokenizer.tokenize(line);
            if (tokens.empty())
            {
                line_no++;
                continue;
            }

            auto p = parser.parse(tokens, line_no);
            auto bytes = encoder.encode(p);

            program.insert(program.end(), bytes.begin(), bytes.end());
            line_no++;
        }

        return program;
    }
};
