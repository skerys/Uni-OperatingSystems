#include "RealMachine.h"

RealMachine::RealMachine() : pager(memory)
{
    pager.setup_vm_paging(vm, 0);
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
    opcode_addr = pager.get_real_addr(opcode_addr, ptr.get_word());

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
    ti.set_status( (isInOut) ? 3 : 1 );
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