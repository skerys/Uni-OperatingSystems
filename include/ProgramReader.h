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
            int lineNo = 0;

            while (std::getline(file, line)) 
            {
                if (line.length() != 4)
                {
                    printf("LEL");
                    file.close();
                    return;
                }
            
                //Convert last two bytes to hexadecimal values
                char str_2[2] = {0};
                str_2[0] = line[2];
                line[2] = isxdigit(line[2]) ? strtol(str_2, NULL, 16) : line[2];

                char str_3[2] = {0};
                str_3[0] = line[3];
                line[3] = isxdigit(line[3]) ? strtol(str_3, NULL, 16) : line[3];
                //------------------------------------------------

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
