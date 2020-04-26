#include <iostream>

#include "Block.h"
#include "RealMachine.h"
#include "VirtualMachine.h"
#include "ProgramReader.h"

int main(int argc, char **argv)
{
   RealMachine    realMachine;
   
   Memory         memory;
   ProgramReader  programReader(memory);
   
   //programReader.set_memory(argv[1]);
 
   //realMachine.run();
}