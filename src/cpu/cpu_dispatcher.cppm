module;
#include <cstdint>
#include <array>
#include <sstream>

export module cpu.dispatcher;

import memory.bus;
import cpu.context;
import instructions.alu;
import instructions.data;

import registers;

export using Instruction = void (*)(CpuContext&);
export using Instructions = std::array<Instruction, 256>;

export class InstructionDispatcher
{
public:
    InstructionDispatcher(CpuContext& context)
        : context(context)
    {
        build_dispatch_table();
    }
    
    void dispatch(uint8_t opcode)
    {
        auto operation = dispatch_table[opcode];

        if (operation)
            operation(context);
        else
            operation_unimplemented();
    }

private:
    CpuContext& context;

    Instructions dispatch_table{};

    void build_dispatch_table()
    {
        dispatch_table.fill(nullptr);
        register_alu_instructions(dispatch_table);
        register_data_instructions(dispatch_table);
    }

    void operation_unimplemented()
    {
        uint16_t pc_val = context.registers.pc.read() - 1;
        uint8_t op = context.bus.read(pc_val);
        std::ostringstream oss;
        oss << "Unimplemented opcode: 0x"
            << std::uppercase << std::hex << static_cast<int>(op);
        throw std::runtime_error(oss.str());
    }
};