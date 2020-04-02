#include <iostream>
#include <io.h>
#include <fcntl.h>

#include "Block.h"
#include "RealMachine.h"
#include "VirtualMachine.h"
#include "ProgramReader.h"


using namespace std;

int main()
{
    /*
    Block           block;
    RealMachine     realMachine;
    Memory          memory;

    block[9]    = 8555;
    block[9].print_bytes();
    block[9][2] = 257;
    block[9].print_bytes();

    memory[3][0].set_int(15);
    memory[3][1].set_int(20);
    memory[0][0].set_bytes('L', 'A', 3, 0);
    memory[0][1].set_bytes('L', 'B', 3, 1);
    memory[0][2].set_bytes('A', 'D', 'D', 'X');
    memory[0][3].set_bytes('W', 'A', 3, 2);
    memory[0][4].set_bytes('H', 'A', 'L', 'T');

    memory[3][0].set_bytes('a', 'b', '.', 'c');
    memory[4][0].set_bytes('d', 'e', '.', 'f');

    memory[5][0].set_bytes('l','a','b','a');
    memory[5][1].set_bytes(' ','d','i','e');
    memory[5][2].set_bytes('n','a',' ','p');
    memory[5][3].set_bytes('o','n','a','i');

    memory[0][0].set_bytes('F', 'O', 3, 0);
    memory[0][1].set_bytes('B','W', 'F', 5);
    memory[0][2].set_bytes('F','C','L','S');
    memory[0][3].set_bytes('H', 'A', 'L', 'T');

    //memory.print();

    //VirtualMachine  virtualMachine(memory);
    //virtualMachine.run();

    //return 0;
    */
   Memory           memory;
   ProgramReader    programReader(memory);

   programReader.setMemory("aaaa.txt");

   //memory = programReader.getMemory();
}