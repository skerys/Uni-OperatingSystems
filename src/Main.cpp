#include <iostream>
#include <io.h>
#include <fcntl.h>

#include "Block.h"
#include "RealMachine.h"
#include "VirtualMachine.h"
#include "ProgramReader.h"

int main(int argc, char **argv)
{  
   Memory         memory;
   ProgramReader  programReader(memory);

   RealMachine    realMachine;
   
   programReader.set_memory(argv[1]);
 
   realMachine.run();
}