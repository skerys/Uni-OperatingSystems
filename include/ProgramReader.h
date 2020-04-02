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

            while (std::getline(file, line)) 
            {
                if (line.length() != 4)
                {
                    printf("LEL");
                    file.close();
                    return;
                }
                    //throw "Smth bad at line %d", lineNo;
                std::cout << line[0];
                memory[lineNo/16][lineNo%16].set_bytes((int)line[0], (int)line[1], (int)line[2], (int)line[3]);

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
