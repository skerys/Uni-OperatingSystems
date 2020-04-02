#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Memory.h"
#include "Register.h"

enum RegisterType { RA, RB };
enum ArithmeticCommand { ADD, SUB, MUL, DIV };
enum JumpType { ALWAYS, IF_EQUAL, IF_NOT_EQUAL, IF_GREATER };

class VirtualMachine
{
private:
    Memory& memory;
    Register ra, rb;            // Bendro naudojimo registrai
    Register ic;                // Komandu skaitiklis
    Flag sf;                    // Pozymio registras
    bool running;
    
    void execute_command();
    Word read_opcode();

    // Write from memory to register: WAxy WBxy
    void writeToMemory(RegisterType registerType, int memoryAddress);

    // Load from memory to register: LAxy LBxy
    void loadFromMemory(RegisterType registerType, int memoryAddress);

    // Do arithmethic commands: ADDX, SUBX, DIVX, MULX
    void arithmethicCommand(ArithmeticCommand type);

    // Do compare: CMPX
    void compareRegisters();

    // Jumps: JPxy, JExy, JNxy, JGxy
    void jumpToAddress(int memoryAddress, JumpType jumpType);

    // Read word from input device: INxy, FRxy
    void readWord(int memoryAddress, bool fromFile);

    // Read block form input device: BINx, BFRx
    void readBlock(int blockNumber, bool fromFile);

    // Write word to output device: OTxy, FWxy
    void writeWord(int wordAddress, bool toFile);

    // Write block to output device: BOTx, BFWx
    void writeBlock(int blockNumber, bool toFile);

    // Open/create file: FOxy
    void openFile(int memoryAddressOfPath);

    // Close file: FCLS
    void closeFile();

    // Delete file: FDEL
    void deleteFile();

    // Stop program: HALT
    void stopProgram();
public:
    VirtualMachine(Memory& _memory) : memory(_memory)
    {
        running = true;
    }
    void loadMemory(Memory& _memory);
    void run();    
    ~VirtualMachine();
};