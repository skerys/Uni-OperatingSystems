#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <stdio.h>
#if _WIN64
#include <io.h>
#elif __APPLE__
#include <sys/uio.h>
#include <unistd.h>
#endif
#include <fcntl.h>
#include <stdlib.h>


#include "Register.h"
#include "Pager.h"
#include "VirtualMachine.h"
#include "Pager.h"

class RealMachine
{
private:
    VirtualMachine virtualMachines[VIRTUAL_MACHINE_NUM];
    Register ra, rb, rc;        // Bendro naudojimo registrai
    Register ptr;               // Puslapiu lenteles registras 
    Register ic;                // Komandu skaitiklis
    Flag sf;                    // Pozymio registras
    Flag mode;                  // Procesoriaus darbo rezimo registras 
    Flag pi, si, ti, oi;        // Pertraukimu (programinių, supervizorinių, taimerio, ivedimo/isvedimo) registrai
    Flag ca, cb, cc;            // Kanalu busenu registrai

    VirtualMachine vm; //for testing with a single vm
    Pager pager;

    Memory memory;

    bool    running;
    bool    isInOut;
public:
    RealMachine();

    void run();

    void load_registers(VirtualMachine virtualMachines);

    void execute_command();

    void change_mode();

    void do_interrupt();

    void reduce_timer();

    void write_registers(VirtualMachine virtualMachines);

    bool interrupt_test();

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
    void deleteFile(int memoryAddressOfPath);

    // Stop program: HALT
    void stopProgram();

    ~RealMachine();
};