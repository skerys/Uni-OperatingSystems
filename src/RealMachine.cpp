#include "RealMachine.h"

RealMachine::RealMachine() : pager(memory)
{
    pager.setup_vm_paging(virtualMachines[0], 0);
}

void RealMachine::run()
{
    load_registers(0);
    execute_command();
    if(interrupt_test())
    {
        change_mode();
        do_interrupt();
    }
    reduce_timer();
    write_registers(0);
}

static constexpr uint16_t combine_two_bytes(uint8_t byteA, uint8_t byteB)
{
    return (uint16_t)byteA * 16 + byteB;
}

Word RealMachine::read_opcode() //word_opcode ic is virtualaus i realu adderss = get. pagery bus funkcija
// ToDo: kad nepamirstume get_real_addr
{
    Word opcode;// = memory[ic.get_value()/16][ic.get_value()%16];
    int real_ic = pager.get_real_addr(ic, ptr.get_word());
    opcode = memory[real_ic / 16][real_ic % 16];
    return opcode;
}

void RealMachine::execute_command()
{
    //Read opcode from address in IC
    Word opcode = read_opcode();
    uint16_t opcode_addr = combine_two_bytes(opcode[2], opcode[3]);
    //opcode_addr = pager.get_real_addr(opcode_addr, ptr.get_word());

    bool jump_happened = false;
    isInOut = false;
    
    switch (combine_two_bytes(opcode[0], opcode[1]))
    {
        case combine_two_bytes('W', 'A'): 
            si = 1;
            rc = opcode_addr;
            break;
        case combine_two_bytes('W', 'B'):
            si = 2;
            rc = opcode_addr;
            break;
        case combine_two_bytes('L', 'A'):
            si = 3;
            rc = opcode_addr;
            break;
        case combine_two_bytes('L', 'B'):
            si = 4;
            rc = opcode_addr;
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
            si = 5;
            rc = opcode_addr;
            isInOut = true;
            break;
        case combine_two_bytes('B', 'I'):
            si = 6;
            rc = opcode[3];
            isInOut = true;
            break;
        case combine_two_bytes('O', 'T'):
            si = 7;
            rc = opcode_addr;
            isInOut = true;
            break;
        case combine_two_bytes('B', 'O'):
            si = 8;
            rc = opcode[3];
            isInOut = true;
            break;
        case combine_two_bytes('W', 'F'):
            si = 9;
            rc = opcode_addr;
            isInOut = true;
            break;
        case combine_two_bytes('B', 'W'):
            si = 10;
            rc = opcode[3];
            isInOut = true;
            break;
        case combine_two_bytes('R', 'F'):
            si = 11;
            rc = opcode_addr;
            isInOut = true;
            break;
        case combine_two_bytes('B', 'R'):
            si = 12;
            rc = opcode[3];
            isInOut = true;
            break;
        case combine_two_bytes('F', 'O'):
            si = 13;
            rc = opcode_addr;
            break;
        case combine_two_bytes('F', 'C'):
            si = 14;
            break;
        case combine_two_bytes('F', 'D'):
            si = 15;
            rc = opcode_addr;
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

void RealMachine::load_program(int index, std::string filename)
{
    ProgramReader programReader(memory, pager, ptr.get_word());
    this->ic = programReader.set_memory(filename);
}

void RealMachine::change_mode()
{}

void RealMachine::do_interrupt()
{}

void RealMachine::reduce_timer()
{
    ti = (isInOut) ? ti.get_status()-3 : ti.get_status()-1;
}

void RealMachine::load_registers(int idx)
{
    ra  = virtualMachines[idx].ra;
    rb  = virtualMachines[idx].rb;
    ic  = virtualMachines[idx].ic;
    sf  = virtualMachines[idx].sf;
    ptr = virtualMachines[idx].ptr;
}

// Pakeitimai
void RealMachine::write_registers(int idx)
{
    virtualMachines[idx].ra  = ra;
    virtualMachines[idx].rb  = rb;
    virtualMachines[idx].ic  = ic;
    virtualMachines[idx].sf  = sf;
    virtualMachines[idx].ptr = ptr;
}

bool RealMachine::interrupt_test()
{ 
    return ( (si.get_status() + pi.get_status() + oi.get_status() == 0) && ((ti.get_status() > 0) ? 0 : 1) ); 
}



RealMachine::~RealMachine()
{

}