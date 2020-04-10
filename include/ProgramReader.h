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
        std::string   line;

        if (file.is_open()) 
        {
            line = setDataBlock(file);

            setCodeBlock(file, line);
            
            file.close();
        }
    }

    char setDigit(char symbol)
    {
        char strInt[2] = {0};
        strInt[0] = symbol;
        
        return isxdigit(symbol) ? strtol(strInt, NULL, 16) : symbol;
    }

    std::string setDataBlock(std::ifstream& file)
    {
        std::string line;
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
                line[i] = setDigit(line[i]);
            }

            int address[4] = { (int)line[1], (int)line[2], (int)line[3], (int)line[4] };

            std::getline(file, line);

            if (line[0] == '$')
            {
                std::string backupLine = line.substr(1, line.length()-1);
                int lineLength         = backupLine.length();

                for (int i = 0; i < lineLength; i += 4)
                {
                    int nullVal = lineLength - i;
                    
                    if (nullVal < 4)
                    {
                        switch(nullVal)
                        {
                            case 1:
                                memory[address[2]][address[3]].set_bytes((int)backupLine[i+0],                    0,                    0, 0);
                                break;
                            case 2:
                                memory[address[2]][address[3]].set_bytes((int)backupLine[i+0], (int)backupLine[i+1],                    0, 0);
                                break;
                            case 3:
                                memory[address[2]][address[3]].set_bytes((int)backupLine[i+0], (int)backupLine[i+1], (int)backupLine[i+2], 0);
                                break;
                            default:
                                break;
                        } 
                    }
                    else
                    {
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
                memory[address[2]][address[3]].set_int(std::stoi(line, nullptr));
            }
            std::getline(file, line);
        }
        return line;
    }

    void setCodeBlock(std::ifstream& file, std::string line)
    {
        int lineNo = 0;

        if (line != "CODE")
        {
            file.close();
            throw "Must be code";
        }

        while (std::getline(file, line)) 
        {
            if (line.length() != 4)
            {
                file.close();
                throw "Error, must be 4 bytes";
            }

            line[2] = setDigit(line[2]);
            line[3] = setDigit(line[3]);

            memory[lineNo/16][lineNo%16].set_bytes((int)line[0], (int)line[1], (int)line[2], (int)line[3]);

            lineNo++;
        }
    }
    
    Memory& getMemory()
    {
        return memory;
    }
};
