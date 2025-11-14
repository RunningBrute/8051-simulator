module;

#include <string>
#include <vector>
#include <cctype>

export module assembler.tokenizer;



export class Tokenizer
{
public:
    using Tokens = std::vector<std::string>;

    Tokens tokenize(const std::string& line) const
    {
        Tokens tokens;
        std::string current;

        for (size_t i = 0; i < line.size(); ++i)
        {
            char c = line[i];

            if (c == ';')
                break;

            if (std::isspace((unsigned char)c))
            {
                flush_current(tokens, current);
                continue;
            }

            if (c == ',' || c == ':' || c == '[' || c == ']')
            {
                flush_current(tokens, current);
                tokens.emplace_back(1, c);
                continue;
            }

            current.push_back(c);
        }

        flush_current(tokens, current);
        return tokens;
    }

private:
    static void flush_current(Tokens& tokens, std::string& current)
    {
        if (!current.empty())
        {
            tokens.push_back(current);
            current.clear();
        }
    }
};
