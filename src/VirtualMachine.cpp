#include "VirtualMachine.h"

static constexpr uint16_t combine_two_bytes(uint8_t byteA, uint8_t byteB)
{
    return (uint16_t)byteA * 0xFF + byteB;
}

VirtualMachine::VirtualMachine()
{
    running = true;
}

Word VirtualMachine::read_opcode()
{
    Word opcode = memory[ic.get_value()/16][ic.get_value()%16];
}

void VirtualMachine::execute_command()
{
    //Read opcode from address in IC
    Word opcode = read_opcode();
    uint16_t opcode_addr = combine_two_bytes(opcode[2], opcode[3]);

    switch (combine_two_bytes(opcode[0], opcode[1]))
    {
        case combine_two_bytes('W', 'A'): //WAxy
            writeToMemory(RegisterType::RA, opcode_addr);
            break;
        case combine_two_bytes('W', 'B'):
            writeToMemory(RegisterType::RB, opcode_addr);
            break;
        case combine_two_bytes('L', 'A'):
            loadFromMemory(RegisterType::RA, opcode_addr);
            break;
        case combine_two_bytes('L', 'B'):
            loadFromMemory(RegisterType::RB, opcode_addr);
            break;
        case combine_two_bytes('A', 'D'):
            arithmethicCommand(ArithmeticCommand::ADD);
            break;
        case combine_two_bytes('S', 'U'):
            arithmethicCommand(ArithmeticCommand::SUB);
            break;
        case combine_two_bytes('M', 'U'):
            arithmethicCommand(ArithmeticCommand::MUL);
            break;
        case combine_two_bytes('D', 'I'):
            arithmethicCommand(ArithmeticCommand::DIV);
            break;
        case combine_two_bytes('C', 'M'):
            compareRegisters();
            break;
        case combine_two_bytes('J', 'P'):
            jumpToAddress(opcode_addr, JumpType::ALWAYS);
            break;
        case combine_two_bytes('J', 'E'):
            jumpToAddress(opcode_addr, JumpType::IF_EQUAL);
            break;
        case combine_two_bytes('J', 'N'):
            jumpToAddress(opcode_addr, JumpType::IF_NOT_EQUAL);
            break;
        case combine_two_bytes('J', 'G'):
            jumpToAddress(opcode_addr, JumpType::IF_GREATER);
            break;
        case combine_two_bytes('I', 'N'):
            readWord(opcode_addr, false);
            break;
        case combine_two_bytes('B', 'I'):
            readBlock(opcode[3], false);
            break;
        case combine_two_bytes('O', 'T'):
            writeWord(opcode_addr, false);
            break;
        case combine_two_bytes('B', 'O'):
            writeBlock(opcode[3], false);
            break;
        case combine_two_bytes('F', 'O'):
            openFile(opcode_addr);
            break;
        case combine_two_bytes('F', 'C'):
            closeFile();
            break;
        case combine_two_bytes('F', 'D'):
            deleteFile();
            break;
        case combine_two_bytes('W', 'F'):
            writeWord(opcode_addr, true);
            break;
        case combine_two_bytes('B', 'W'):
            writeBlock(opcode[3], true);
            break;
        case combine_two_bytes('R', 'F'):
            readWord(opcode_addr, true);
            break;
        case combine_two_bytes('B', 'R'):
            readBlock(opcode[3], true);
            break;
        case combine_two_bytes('H', 'A'):
            stopProgram();
            break;
        default:
            printf("Uoj pajebaaaat\n");
            exit(0);
            break;
        }
    //switch opcode and increase IC by 1 in cases where there is no jump
}
    
void VirtualMachine::loadMemory(Memory _memory)
{
    memory = _memory;
}

void VirtualMachine::run()
{
    while(running)
    {
        execute_command();
    }
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

//Read word from input device: INxy, FRxy
void VirtualMachine::readWord(int memoryAddress, bool fromFile)
{

}

//Read block form input device: BINx, BFRx
void VirtualMachine::readBlock(int blockNumber, bool fromFile)
{

}

//Write word to output device: OTxy, FWxy
void VirtualMachine::writeWord(int wordAddress, bool toFile)
{

}

//Write block to output device: BOTx, BFWx
void VirtualMachine::writeBlock(int blockNumber, bool toFile)
{

}

//Open/create file: FOxy
void VirtualMachine::openFile(int memoryAddressOfPath)
{

}

//Close file: FCLS
void VirtualMachine::closeFile()
{

}

//delete file: FDEL
void VirtualMachine::deleteFile()
{

}

//stop program: HALT
void VirtualMachine::stopProgram()
{
    running = false;
}

VirtualMachine::~VirtualMachine()
{

}