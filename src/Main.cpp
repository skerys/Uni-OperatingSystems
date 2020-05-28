#include <iostream>

#include "Kernel.h"
#include "Block.h"
#include "RealMachine.h"
#include "VirtualMachine.h"
#include "ProgramReader.h"

int main(int argc, char **argv)
{  
   RealMachine    realMachine;
   Kernel         kernel(realMachine);

   //realMachine.run_program(argv[1]);
   //realMachine.run_program("source.a");
   
   // Kernel
   // StartStop (running)
      // kuria proce
      // kuria res
   // ProcPlanu
   // ResDistr
   kernel.run_real_machine();

   realMachine.run();
}