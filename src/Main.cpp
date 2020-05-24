#include <iostream>

#include "Block.h"
#include "RealMachine.h"
#include "VirtualMachine.h"
#include "ProgramReader.h"

int main(int argc, char **argv)
{
   RealMachine    realMachine;
   
   realMachine.run_program(argv[1]);
   //realMachine.run_program("source.a");
   
   realMachine.run();
}