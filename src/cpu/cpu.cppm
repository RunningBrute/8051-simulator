module;
#include <cstdint>
#include <array>
#include <iostream>
#include <iomanip>
#include <sstream>

export module cpu;

import cpu.alu;
import memory.bus;
import cpu.registers;
import cpu.dispatcher;
import cpu.fetcher;
import cpu.context;
import logger;

export class CPU
{
public:
    CPU(MemoryBus& bus) 
        : context(bus), dispatcher(context)
    {}
    
    void reset();
    void step();

    MemoryBus& get_bus() { return context.bus; }
    const MemoryBus& get_bus() const { return context.bus; }
    ALU& get_alu() { return context.alu; }
    const ALU& get_alu() const { return context.alu; }
    CpuContext& get_context() { return context; }
    const CpuContext& get_context() const { return context; }

private:
    CpuContext context;
    InstructionDispatcher dispatcher;
};

module :private;

void CPU::reset()
{
    context.registers.acc.write(0x00);
    context.registers.b.write(0x00);
    context.registers.sp.write(0x07);
    context.registers.pc.write(0x0000);
    context.registers.dptr.write(0x0000);
    context.registers.psw.write(0x00);
    context.registers.rbank.reset();
}

void CPU::step()
{
    auto pc_val = context.registers.pc.read();
    auto opcode = context.fetcher.fetch8();

    std::ostringstream oss;
    oss << "Executing opcode 0x"
        << std::uppercase << std::hex
        << static_cast<int>(opcode)
        << " at PC=0x" << std::setw(4) << std::setfill('0') << pc_val;

    AppLogger::debug(oss.str()); 

    dispatcher.dispatch(opcode);
}