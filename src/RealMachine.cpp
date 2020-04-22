#include "RealMachine.h"

RealMachine::RealMachine()
{}

void RealMachine::run()
{
    load_registers(virtualMachines[0]);
    execute_command();
    if(interrupt_test())
    {
        change_mode();
        do_interrupt();
    }
    reduce_timer();
    write_registers(virtualMachines[0]);
}

void RealMachine::load_registers(VirtualMachine virtualMachines)
{}

static constexpr uint16_t combine_two_bytes(uint8_t byteA, uint8_t byteB)
{
    return (uint16_t)byteA * 16 + byteB;
}

Word RealMachine::read_opcode() //word_opcode ic is virtualaus i realu adderss = get. pagery bus funkcija
// ToDo: kad nepamirstume get_real_addr
{
    Word opcode;// = memory[ic.get_value()/16][ic.get_value()%16];
    return opcode;
}

void RealMachine::execute_command()
{
    //Read opcode from address in IC
    Word opcode = read_opcode();
    uint16_t opcode_addr = combine_two_bytes(opcode[2], opcode[3]);

    bool jump_happened = false;

    switch (combine_two_bytes(opcode[0], opcode[1]))
    {
        case combine_two_bytes('W', 'A'): 
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
            jump_happened = true;
            break;
        case combine_two_bytes('J', 'E'):
            jumpToAddress(opcode_addr, JumpType::IF_EQUAL);
            jump_happened = true;
            break;
        case combine_two_bytes('J', 'N'):
            jumpToAddress(opcode_addr, JumpType::IF_NOT_EQUAL);
            jump_happened = true;
            break;
        case combine_two_bytes('J', 'G'):
            jumpToAddress(opcode_addr, JumpType::IF_GREATER);
            jump_happened = true;
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
            deleteFile(opcode_addr);
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
            throw "Exception which needs to be implemented; Unknown opcode\n";
            exit(0);
            break;
        }
    
    if (!jump_happened)
    {
        ++ic;
    }
}

void RealMachine::change_mode()
{}

void RealMachine::do_interrupt()
{}

void RealMachine::reduce_timer()
{
    ti.set_status( (isInOut) ? 3 : 1 );
}

void RealMachine::load_registers(VirtualMachine virtualMachines)
{
    ra  = virtualMachines.ra;
    rb  = virtualMachines.rb;
    ic  = virtualMachines.ic;
    sf  = virtualMachines.sf;
    ptr = virtualMachines.ptr;
}

void RealMachine::write_registers(VirtualMachine virtualMachines)
{
    virtualMachines.ra  = ra;
    virtualMachines.rb  = rb;
    virtualMachines.ic  = ic;
    virtualMachines.sf  = sf;
    virtualMachines.ptr = ptr;
}

bool RealMachine::interrupt_test()
{ 
    return ( (si.get_status() + pi.get_status() + oi.get_status() == 0) && ((ti.get_status() > 0) ? 0 : 1) ); 
}



RealMachine::~RealMachine()
{

}