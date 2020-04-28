#include "RealMachine.h"

// Do arithmethic commands: ADDX, SUBX, DIVX, MULX
void RealMachine::arithmethicCommand(ArithmeticCommand arithmeticCommand)
{
    switch(arithmeticCommand)
    {
        case ArithmeticCommand::ADD:
            ra.set_value(ra.get_value() + rb.get_value());
            break;
        case ArithmeticCommand::SUB:
            ra.set_value(ra.get_value() - rb.get_value());
            break;
        case ArithmeticCommand::MUL:
            ra.set_value(ra.get_value() * rb.get_value());
            break;
        case ArithmeticCommand::DIV:
            ra.set_value(ra.get_value() / rb.get_value());
            break;
        default:
            throw "Exception which needs to be implemented; Unknown command\n";
            break;
    }
}

// Do compare: CMPX
void RealMachine::compareRegisters()
{
    if (ra.get_value() == rb.get_value())
        sf.set_status(0);
    else if (ra.get_value() > rb.get_value())
        sf.set_status(1);
    else
        sf.set_status(2);     
}

// Jumps: JPxy, JExy, JNxy, JGxy
void RealMachine::jumpToAddress(int memoryAddress, JumpType jumpType)
{
    switch(jumpType)
    {
        case JumpType::ALWAYS:
            ic.set_value(memoryAddress);
            break;
        case JumpType::IF_EQUAL:
            if (sf.get_status() == 0)
                ic.set_value(memoryAddress);
            break;
        case JumpType::IF_NOT_EQUAL:
            if (sf.get_status() != 0)
                ic.set_value(memoryAddress);
            break;
        case JumpType::IF_GREATER:
            if (sf.get_status() == 1)
                ic.set_value(memoryAddress);
            break;
        default:
            throw "Exception which needs to be implemented; Unknown jumptype\n";
            break;
    }
}

// Stop program: HALT
void RealMachine::stopProgram()
{
    running = false;
}