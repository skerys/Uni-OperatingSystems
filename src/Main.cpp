#include <iostream>
#include <io.h>
#include <fcntl.h>

#include "Block.h"
#include "RealMachine.h"
#include "VirtualMachine.h"
#include "ProgramReader.h"

int main(int argc, char **argv)
{
   Memory           memory;
   ProgramReader    programReader(memory);
   
   programReader.setMemory(argv[1]);

   VirtualMachine vm(memory);
   vm.run(); 

}