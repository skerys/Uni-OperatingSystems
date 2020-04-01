#include "VirtualMachine.h"

VirtualMachine::VirtualMachine()
{
    running = true;
}

void VirtualMachine::execute()
{
    std::cout << "Hello, guys";
}

void VirtualMachine::execute_command()
{
    
}
    
void VirtualMachine::loadMemory(Memory _memory)
{
    memory = _memory;
}

void VirtualMachine::run()
{

}

//Write from memory to register: WAxy WBxy
void VirtualMachine::writeToMemory(RegisterType registerType, int memoryAddress)
{
    switch(registerType)
    {
        case RegisterType::RA:
            memory[memoryAddress/16][memoryAddress%16] = ra.get_value();
            break;
        case RegisterType::RB:
            memory[memoryAddress/16][memoryAddress%16] = rb.get_value();
            break;
        default:
            printf("No such register");
            break;
    }
}

//Load from memory to register: LAxy LBxy
void VirtualMachine::loadFromMemory(RegisterType registerType, int memoryAddress)
{
    switch(registerType)
    {
        case RegisterType::RA:
            ra.set_value(memory[memoryAddress/16][memoryAddress%16].get_int());
            break;
        case RegisterType::RB:
            rb.set_value(memory[memoryAddress/16][memoryAddress%16].get_int());
            break;
        default:
            printf("No such register");
            break;
    }
}

//Do arithmethic commands: ADDX, SUBX, DIVX, MULX
void VirtualMachine::arithmethicCommand(ArithmeticCommand arithmeticCommand)
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
            printf("No such command");
            break;
    }
}

//Do compare: CMPX
void VirtualMachine::compareRegisters()
{
    if (ra.get_value() == rb.get_value())
        sf.set_status(0);
    else if (ra.get_value() > rb.get_value())
        sf.set_status(1);
    else
        sf.set_status(2);     
}

//Jumps: JPxy, JExy, JNxy, JGxy
void VirtualMachine::jumpToAddress(int memoryAddress, JumpType jumpType)
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
            printf("No such jumptype");
            break;
    }
}

VirtualMachine::~VirtualMachine()
{

}