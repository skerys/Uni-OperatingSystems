#include <stdio.h>
#include "VirtualMachine.h"
#include <io.h>
#include <fcntl.h>
#include <io.h>
#include <stdlib.h>
#include <stdio.h>
#include <share.h>

#define _POSIX_C_SOURCE 200809L

#include "VirtualMachine.h"

static constexpr uint16_t combine_two_bytes(uint8_t byteA, uint8_t byteB)
{
    return (uint16_t)byteA * 16 + byteB;
}

Word VirtualMachine::read_opcode()
{
    Word opcode = memory[ic.get_value()/16][ic.get_value()%16];
    return opcode;
}

void VirtualMachine::execute_command()
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

// Write from memory to register: WAxy WBxy
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
            throw "Exception which needs to be implemented; Unknown register\n";
            break;
    }
}

// Load from memory to register: LAxy LBxy
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
            throw "Exception which needs to be implemented; Unknown register\n";
            break;
    }
}

// Do arithmethic commands: ADDX, SUBX, DIVX, MULX
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
            throw "Exception which needs to be implemented; Unknown command\n";
            break;
    }
}

// Do compare: CMPX
void VirtualMachine::compareRegisters()
{
    if (ra.get_value() == rb.get_value())
        sf.set_status(0);
    else if (ra.get_value() > rb.get_value())
        sf.set_status(1);
    else
        sf.set_status(2);     
}

// Jumps: JPxy, JExy, JNxy, JGxy
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
            throw "Exception which needs to be implemented; Unknown jumptype\n";
            break;
    }
}

// Read word from input device: INxy, FRxy
void VirtualMachine::readWord(int memoryAddress, bool fromFile)
{
    if (fromFile)
    {
        char word[WORD_LENGTH] = {0, 0, 0, 0};
        int fd = rb.get_value();

        FILE * file = _fdopen(fd, "r");
        int a;
        fscanf(file, "%d", &a);

        memory[memoryAddress/16][memoryAddress%16] = a;
        /*_read( fd, word, WORD_LENGTH);

        memory[memoryAddress/16][memoryAddress%16].set_bytes(word[0], word[1], word[2], word[3]);*/
    }
    else
    {
        /*if (std::cin.peek() == '$')
        {
            Word word;
            char sym;
            int index = 0;

            // "Eat" the dollar sign
            std::cin.get(sym);

            while(std::cin.get(sym) && index < 4)
            {
                word[index] = sym;
                index++;
            }

            memory[memoryAddress/16][memoryAddress%16] = word;
        }
        else
        {*/
        int num;

        std::cin >> num;
        std::cin.get(); //eat new line

        memory[memoryAddress/16][memoryAddress%16] = num;
        
    }
}

// Read block form input device: BINx, BFRx
void VirtualMachine::readBlock(int blockNumber, bool fromFile)
{
    if (fromFile)
    {
        char word[WORD_LENGTH] = {0, 0, 0, 0};
        int fd = rb.get_value();
        int bytesRead = 0;
        int wordIndex = 0;

        while (((bytesRead = _read( fd, word, WORD_LENGTH)) > 0) && (wordIndex < BLOCK_LENGTH))
        {
            memory[blockNumber][wordIndex].set_bytes(word[0], word[1], word[2], word[3]);
            wordIndex++;
        }
    }
    else
    {
        // char start = std::cin.peek();

        // if (start == '$')
        // {
        Word word;
        char sym;
        int byteIndex = 0;
        int wordIndex = 0;

        while (wordIndex < 16)
        {
            byteIndex = 0;
            while(std::cin.get(sym) && byteIndex < 4)
            {
                if(sym == '\n') break;
                word[byteIndex] = sym;
                byteIndex++;
            }
            memory[blockNumber][wordIndex] = word;
            wordIndex++;
            
            if (byteIndex < 4)
                break;
        }
        // }
        // else
        // {
        //     int num;
        //     int address = 0;

        //     while(std::cin >> num && address < 16)
        //     {
        //         memory[blockNumber][address] = num;
        //         address++;
        //     }
        // }
    }
}

// Write word to output device: OTxy, FWxy
void VirtualMachine::writeWord(int wordAddress, bool toFile)
{
    if (toFile)
    {
        int fd = rb;

        std::string toWrite;

        toWrite = std::to_string(memory[wordAddress/16][wordAddress%16].get_int());
         _write(fd, toWrite.c_str(), toWrite.length());
    }
    else
    {
        
        int number = memory[wordAddress/16][wordAddress%16].get_int();

        std::cout << number << " " << std::endl;

    }
}

// Write block to output device: BOTx, BFWx
void VirtualMachine::writeBlock(int blockNumber, bool toFile)
{
    int address = 0;
    uint8_t symbol = 0;

    if (toFile)
    {
        int fd = rb;
        std::string toWrite;

        while(address < 16)
        {
            toWrite = "";
            for (int i = 0; i < 4; ++i)
            {
                symbol = memory[blockNumber][address][i];
                if(symbol == 0) break;
                toWrite.push_back(symbol);
            }
            _write(fd, toWrite.c_str(), toWrite.length());
            if(symbol == 0) break;
            address++;
        }
    }
    else
    {
        while(address < 16)
        {
            for (int i = 0; i < 4; ++i)
            {
                symbol = memory[blockNumber][address][i];
                if(symbol == 0) break;
                std::cout << (char)symbol;
            }
            if(symbol == 0) break;
            address++;
        }
    }
}

// Open/create file: FOxy
void VirtualMachine::openFile(int memoryAddressOfPath)
{
    std::string path;
    int pathAddress = memoryAddressOfPath;
    int byteIndex = 0;

    char symbol = memory[pathAddress/16][pathAddress%16][byteIndex];
    while(symbol != 0)
    {
        path.push_back(symbol);
        
        byteIndex++;
        if(byteIndex >= 4){
            byteIndex = 0;
            pathAddress++;
        }

         symbol = memory[pathAddress/16][pathAddress%16][byteIndex];
    }

    int file = _open(path.c_str(), _O_CREAT | _O_RDWR, S_IREAD | _S_IWRITE);
    //Store file descriptor in RB
    rb = file;

}

// Close file: FCLS
void VirtualMachine::closeFile()
{
    //FILE* file = fdopen(rb, "rw");
    //fclose(file);
    _close(rb);
}

// Delete file: FDxy
void VirtualMachine::deleteFile(int memoryAddressOfPath)
{
    std::string path;
    int pathAddress = memoryAddressOfPath;
    int byteIndex = 0;

    char symbol = memory[pathAddress/16][pathAddress%16][byteIndex];
    while(symbol != 0)
    {
        path.push_back(symbol);
        
        byteIndex++;
        if(byteIndex >= 4){
            byteIndex = 0;
            pathAddress++;
        }

         symbol = memory[pathAddress/16][pathAddress%16][byteIndex];
    }

    remove(path.c_str());
}

// Stop program: HALT
void VirtualMachine::stopProgram()
{
    running = false;
}

void VirtualMachine::loadMemory(Memory& _memory)
{
    memory = _memory;
}


void VirtualMachine::run()
{
    ic = 0;
    while(running)
    {
#if DEBUG_MODE
        do_debug();
        execute_command();
#else
        execute_command();
#endif
    }
}

void VirtualMachine::do_debug()
{
    printf("\nRegister values: RA: %X; RB: %X; IC:%X; SF:%X\n", ra.get_value(), rb.get_value(), ic.get_value(), sf.get_status());
    Word nextCommand = memory[ic/16][ic%16];

    if(nextCommand[2] <= 15){
        nextCommand[2] = nextCommand[2] >= 10 ? 'A' + nextCommand[2] - 10 : '0' + nextCommand[2];
    }
    if(nextCommand[3] <= 15){
        nextCommand[3] = nextCommand[3] >= 10 ? 'A' + nextCommand[3] - 10 : '0' + nextCommand[3];
    }
    printf("\nNext command: %c%c%c%c\n", nextCommand[0], nextCommand[1], nextCommand[2], nextCommand[3]);
    memory.print();

    printf("\nPress any key to run the next command...");
    std::cin.get();
    printf("\nRunning command %c%c%c%c\n", nextCommand[0], nextCommand[1], nextCommand[2], nextCommand[3]);
    


}

void VirtualMachine::set_ptr(Word word)
{
    ptr.set_value(word.get_int());
}

VirtualMachine::~VirtualMachine()
{

}