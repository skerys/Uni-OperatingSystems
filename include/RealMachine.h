#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <stdio.h>
#if _WIN32 || _WIN64
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
#include "ProgramReader.h"

class RealMachine
{
private:
    VirtualMachine virtualMachines[VIRTUAL_MACHINE_NUM];

    bool activeVm[VIRTUAL_MACHINE_NUM];
    int currentActiveVm;

    Register ra, rb, rc;        // Bendro naudojimo registrai
    Register ptr;               // Puslapiu lenteles registras 
    Register ic;                // Komandu skaitiklis
    Flag sf;                    // Pozymio registras
    Flag mode;                  // Procesoriaus darbo rezimo registras 
    Flag pi, si, ti, oi;        // Pertraukimu (programinių, supervizorinių, taimerio, ivedimo/isvedimo) registrai
    Flag ca, cb, cc;            // Kanalu busenu registrai

    Pager pager;

    Memory memory;

    bool    running;
    bool    isInOut;
public:
    RealMachine();
    void load_program(int index, std::string filename);
    void run_program(std::string filename);

    void debug_rm();
    void print_registers();
    void print_vm_memory();
    void print_next_command_info();

    //Main running loop
    void run();
    //Command execution
    Word read_opcode();
    void execute_command();
    //Register writing/loading to/from specific vm
    void load_registers(int idx);
    void write_registers(int idx);
    //Checking and handling interrupts
    bool interrupt_test();
    void handle_interrupt();
    void change_mode(bool newValue);
    void reduce_timer();

    //BASE COMMAND LOGIC:

    // Do arithmethic commands: ADDX, SUBX, DIVX, MULX
    void arithmethicCommand(ArithmeticCommand type);
    // Do compare: CMPX
    void compareRegisters();
    // Jumps: JPxy, JExy, JNxy, JGxy
    void jumpToAddress(int memoryAddress, JumpType jumpType);
    // Stop program: HALT
    void stopProgram();

    //SYSTEM INTERRUPT LOGIC:

    // Write from memory to register: WAxy WBxy; SI = 1 or 2
    void write_to_memory(RegisterType registerType);
    // Load from memory to register: LAxy LBxy; SI = 3 or 4
    void load_from_memory(RegisterType registerType);
    // Read word from input device: INxy, FRxy; SI = 5 or 11
    void read_word(bool fromFile);
    // Read block form input device: BINx, BFRx; SI = 6 or 12
    void read_block(bool fromFile);
    // Write word to output device: OTxy, FWxy; SI = 7 or 9
    void write_word(bool toFile);
    // Write block to output device: BOTx, BFWx; SI = 8 or 10
    void write_block(bool toFile);
    // Open/create file: FOxy
    void open_file();
    // Close file: FCLS
    void close_file();
    // Delete file: FDEL
    void delete_file();

    void do_timer_interrupt();

    ~RealMachine();
};