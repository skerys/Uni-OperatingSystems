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
            break;
    }
}

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
            break;
    }
}

void VirtualMachine::compareRegisters()
{
    if (ra.get_value() == rb.get_value())
        sf.set_status(0);
    else if (ra.get_value() > rb.get_value())
        sf.set_status(1);
    else
        sf.set_status(2);    
}

VirtualMachine::~VirtualMachine()
{

}