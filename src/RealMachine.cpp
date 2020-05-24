#include "RealMachine.h"

static bool skipToNextCmd = false;

RealMachine::RealMachine() : pager(memory)
{
    pager.setup_vm_paging(virtualMachines[0], 0);
    ti = 10;
    activeVm[0] = true;
    for(int i = 1; i <= 3; ++i)
    {
        activeVm[i] = false;
    }
    currentActiveVm = 0;
}

void RealMachine::run()
{
    while(running)
    {
        debug_rm();
        execute_command();
        if(interrupt_test())
        {
            if(!skipToNextCmd) debug_rm();
            change_mode(true);
            if(!skipToNextCmd) debug_rm();
            handle_interrupt();
            change_mode(false);
        }
        reduce_timer();
        if(ti.get_status() <= 0)
        {
            if(!skipToNextCmd) debug_rm();
            change_mode(true);
            if(!skipToNextCmd) debug_rm();
            do_timer_interrupt();
        }
        
    }
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
            pi = 2;
            fprintf(stderr, "Incorrect operation code");
            exit(1);
            break;
        }
    
    if (!jump_happened)
    {
        ++ic;

        if ((ic < 0) && (ic > 255))
        {
            pi = 1;
            fprintf(stderr, "Incorrect address");
            exit(1);
        }
    }
}

void RealMachine::load_program(int index, std::string filename)
{
    ProgramReader programReader(memory, pager, ptr.get_word());
    this->ic = programReader.set_memory(filename);
}

void RealMachine::run_program(std::string filename)
{
    load_registers(0);
    load_program(0, filename);
    running = true;
}

void RealMachine::change_mode(bool newValue)
{
    mode = (int)newValue;
}

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
    return (si.get_status() + pi.get_status() + oi.get_status() != 0); 
}

void RealMachine::debug_rm()
{
    skipToNextCmd = false;
    bool looping = true;
    while(looping)
    {
        printf("\n");
        print_registers();
        print_next_command_info();
        printf("\nPrint (R)M Memory; Print (V)M Memory;\n");
        printf("(S)mall step; Skip To next (C)ommand\n");
        printf("Select next action: ");
        char action = std::cin.get();
        fflush(stdin);
        switch (action)
        {
            case 's':
            case 'S':
                looping = false;
                break;
            case 'r':
            case 'R':
                memory.print();
                break;
            case 'v':
            case 'V':
                print_vm_memory();
                break;
            case 'c':
            case 'C':
                looping = false;
                skipToNextCmd = true;
                break;
            default:
                looping = true;
        }
    }
}

void RealMachine::print_registers()
{
    printf("\e[1mRA\e[0m: %4X     \e[1mSF\e[0m: %4X     \e[1mPI\e[0m: %4X     \e[1mTI\e[0m: %4X\n", ra.get_value(), sf.get_status(), pi.get_status(), ti.get_status());
    printf("\e[1mRB\e[0m: %4X     \e[1mMODE\e[0m: %2X     \e[1mSI\e[0m: %4X\n", rb.get_value(), mode.get_status(), si.get_status());
    printf("\e[1mRC\e[0m: %4X     \e[1mPTR\e[0m: %3X     \e[1mOI\e[0m: %4X     \e[1mIC\e[0m: %4X\n", rc.get_value(), ptr.get_value(), oi.get_status(), ic.get_value());
}

void RealMachine::print_next_command_info()
{
    int realAddr = pager.get_real_addr(ic, ptr.get_word());
    Word nextCommand = memory[realAddr/16][realAddr%16];

    if(nextCommand[2] <= 15)
    {
        nextCommand[2] = nextCommand[2] >= 10 ? 'A' + nextCommand[2] - 10 : '0' + nextCommand[2];
    }
    if(nextCommand[3] <= 15)
    {
        nextCommand[3] = nextCommand[3] >= 10 ? 'A' + nextCommand[3] - 10 : '0' + nextCommand[3];
    }
    printf("\nNext command: %c%c%c%c; Virtual address(IC): %X; Real address %X\n", nextCommand[0], nextCommand[1], nextCommand[2], nextCommand[3], ic.get_value(), realAddr);
}

void RealMachine::print_vm_memory()
{
    for(int i = 0; i < 16; ++i)
    {
        printf("\e[1m%2X: \e[0m", i);
        int realBlock = pager.get_read_block(i, ptr.get_word());
        for(int j = 0; j < BLOCK_LENGTH; ++j)
        {
            memory[realBlock][j].print();
        }
        printf("\n");
    }
}


RealMachine::~RealMachine()
{

}