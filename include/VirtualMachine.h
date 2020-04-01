#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Memory.h"
#include "Register.h"

enum RegisterType{
    RA, RB
};

enum ArithmeticCommand{
    ADD, SUB, MUL, DIV
};

enum JumpType{
    ALWAYS, IF_EQUAL, IF_NOT_EQUAL, IF_GREATER
};

class VirtualMachine
{
private:
    Memory memory;
    Register ra, rb;
    Register ic;
    Flag sf;
    bool running;
    void execute();
    void execute_command();
public:
    VirtualMachine();
    void loadMemory(Memory _memory);
    void run();

    //Write from memory to register: WAxy WBxy
    void writeToMemory(RegisterType register, int memoryAddress);
    //Load from memory to register: LAxy LBxy
    void loadFromMemory(RegisterType register, int memoryAddress);
    //Do arithmethic commands: ADDX, SUBX, DIVX, MULX
    void arithmethicCommand(ArithmeticCommand type);
    //Do compare: CMPX
    void compareRegisters();
    //Jumps: JPxy, JExy, JNxy, JGxy
    void jumpToAddress(int memoryAddress, JumpType jumpType);
    //Read word from input device: INxy, FRxy
    void readWord(int memoryAddress, bool fromFile);
    //Read block form input device: BINx, BFRx
    void readBlock(int blockNumber, bool fromFile);
    //Write word to output device: OTxy, FWxy
    void writeWord(int wordAddress, bool toFile);
    //Write block to output device: BOTx, BFWx
    void writeBlock(int blockNumber, bool toFile);
    //Open/create file: FOxy
    void openFile(int memoryAddressOfPath);
    //Close file: FCLS
    void closeFile();
    //delete file: FDEL
    void deleteFile();
    //stop program: HALT
    void stopProgram();
    


    ~VirtualMachine();
};

enum CommandCode
{
    WAxy,
    WBxy,
    LAxy,
    LBxy,
    ADDX,
    SUBX,
    MULX,
    DIVX,
    CMPX,
    JPxy,
    JExy,
    JNxy,
    JGxy,
    INxy,
    BINx,
    OTxy,
    BOTx,
    FOxy,
    FCLS,
    FDEL,
    FWxy,
    BFWx,
    FRxy,
    BFRx,
    HALT
};
