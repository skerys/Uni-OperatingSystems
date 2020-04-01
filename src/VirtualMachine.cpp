#include "VirtualMachine.h"

static constexpr uint16_t combine_two_bytes(uint8_t byteA, uint8_t byteB)
    {
        return (uint16_t)byteA * 0xFF + byteB;
    }

VirtualMachine::VirtualMachine()
{
    this->running = true;
}

void VirtualMachine::execute()
{
    std::cout << "Hello, guys";
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

VirtualMachine::~VirtualMachine()
{

}