#pragma once

#include <fstream>

#include "Memory.h"

class ProgramReader
{
private:
    Memory& memory;
public:
    ProgramReader(Memory& _memory) : memory(_memory)
    {

    }

    void setMemory(std::string filename)
    {       
        std::ifstream file(filename);
        char sym;

        if (file.is_open()) 
        {
            std::string line;
            int lineNo;

            std::getline(file, line);
            if (line != "DATA")
            {
                file.close();
                throw "Must be data";
            }

            std::getline(file, line);
            
            while(line[0] == '[')
            {
                int address[4] = { (int)line[1], (int)line[2], (int)line[3], (int)line[4] };

                std::getline(file, line);

                for (int i = 0; (line.length()-1) > 1; ++i)
                {
                    memory[address[0]*16+address[1]][address[2]*16+address[3]].set_bytes((int)line[i+0], (int)line[i+1], (int)line[i+2], (int)line[i+3]);
                }

                std::getline(file, line);
            }

            if (line != "CODE")
            {
                file.close();
                throw "Must be code";
            }

            while (std::getline(file, line)) 
            {
                 if (line[0] == '[')
                {
                    int address[4] = { (int)line[1], (int)line[2], (int)line[3], (int)line[4] };
                }
                else
                {
                    throw "Must be address";
                }
                

                if (line.length() != 8)
                {
                    file.close();
                    throw "Error, must be 4 bytes";
                }
                
                memory[lineNo/16][lineNo%16].set_bytes((int)line[4], (int)line[5], (int)line[6], (int)line[7]);

                lineNo++;
            }
            file.close();
        }
    }
    
    Memory& getMemory()
    {
        return memory;
    }
};
