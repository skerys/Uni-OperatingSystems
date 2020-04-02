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
