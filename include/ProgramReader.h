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
            char str[2] = {0};
            std::string line;
            std::string backupLine;

            std::getline(file, line);
            if (line != "DATA")
            {
                file.close();
                throw "Must be data";
            }

            std::getline(file, line);
            
            while(line[0] == '[')
            {
                for(int i = 1; i < 5; ++i)
                {
                    str[0] = str[1] = 0;
                    str[0] = line[i];
                    line[i] = isxdigit(line[i]) ? strtol(str, NULL, 16) : line[i];
                }

                int address[4] = { (int)line[1], (int)line[2], (int)line[3], (int)line[4] };

                std::getline(file, line);

                int lineLength = 0;

                if (line[0] == '$')
                {
                    backupLine = line.substr(1, line.length()-1);
                    lineLength = backupLine.length();

                    for (int i = 0; i < lineLength; i+=4)
                    {
                        int nullVal = lineLength-i;
                        
                        if (nullVal < 4)
                        {
                            switch(nullVal)
                            {
                                case 1:
                                    memory[address[2]][address[3]].set_bytes((int)backupLine[i+0], 0, 0, 0);
                                    break;
                                case 2:
                                    memory[address[2]][address[3]].set_bytes((int)backupLine[i+0], (int)backupLine[i+1], 0, 0);
                                    break;
                                case 3:
                                    memory[address[2]][address[3]].set_bytes((int)backupLine[i+0], (int)backupLine[i+1], (int)backupLine[i+2], 0);
                                    break;
                                default:
                                    break;
                            } 
                        }
                        else{
                            memory[address[2]][address[3]].set_bytes((int)backupLine[i+0], (int)backupLine[i+1], (int)backupLine[i+2], (int)backupLine[i+3]);
                        }

                        address[3]++;
                        if(address[3] >= 16)
                        {
                            address[3] = 0;
                            address[2]++;
                        }
                    }
                }
                else
                {
                    backupLine = line.length();
                    lineLength = backupLine.length();

                    memory[address[2]][address[3]].set_int(std::stoi(backupLine));
                }
                std::getline(file, line);
            }

            if (line != "CODE")
            {
                file.close();
                throw "Must be code";
            }

            int lineNo = 0;
            while (std::getline(file, line)) 
            {
                /*if (line[0] == '[')
                {
                    int address[4] = { (int)line[1], (int)line[2], (int)line[3], (int)line[4] };
                }
                else
                {
                    throw "Must be address";
                }*/
                

                if (line.length() != 4)
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
