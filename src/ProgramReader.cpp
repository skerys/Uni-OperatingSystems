#include <fstream>

#include "ProgramReader.h"

int ProgramReader::set_memory(std::string filename)
{       
    int ic;
    std::string line;

    file.open(filename);

    if (file.is_open()) 
    {
        line = set_datablock();
        ic   = set_codeblock(line);
        file.close();
    }
    return ic;
}

char ProgramReader::set_digit(char symbol)
{
    char strInt[2] = {0};
    strInt[0] = symbol;
    
    return isxdigit(symbol) ? strtol(strInt, NULL, 16) : symbol;
}

std::string ProgramReader::set_datablock()
{
    std::string line;
    std::getline(file, line);

    if (line == "DATA")
    {
        std::getline(file, line);
        
        while(line[0] == '[')
        {
            int address[2];
            
            for (int i = 1; i < 3; ++i)
                address[i-1] = set_digit(line[i]);

            int virtual_addr = address[0] * 16 + address[1];
            int real_addr    = pager.get_real_addr(virtual_addr, ptr);

            int block_addr  = real_addr / 16;
            int word_addr   = real_addr % 16;

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
                                memory[block_addr][word_addr].set_bytes((int)backupLine[i+0],                    0,                    0, 0);
                                break;
                            case 2:
                                memory[block_addr][word_addr].set_bytes((int)backupLine[i+0], (int)backupLine[i+1],                    0, 0);
                                break;
                            case 3:
                                memory[block_addr][word_addr].set_bytes((int)backupLine[i+0], (int)backupLine[i+1], (int)backupLine[i+2], 0);
                                break;
                            default:
                                break;
                        } 
                    }
                    else
                    {
                        memory[block_addr][word_addr].set_bytes((int)backupLine[i+0], (int)backupLine[i+1], (int)backupLine[i+2], (int)backupLine[i+3]);
                    }
                    word_addr++;
                    virtual_addr++;

                    if(word_addr >= 16)
                    {
                        real_addr   = pager.get_real_addr(virtual_addr, ptr);

                        block_addr  = real_addr / 16;
                        word_addr   = real_addr % 16;
                    }
                }
            }
            else
                memory[block_addr][word_addr].set_int(std::stoi(line, nullptr));

            std::getline(file, line);
        }
    }
    return line;
}

int ProgramReader::set_codeblock(std::string line)
{
    int virtual_addr;
    int real_addr;

    int ic;

    int block_addr;
    int word_addr;

    if (line != "CODE")
        reading_error("Must be code");

    std::getline(file, line);
        
    if (line[0] == '[')
    {
        int address[2];
            
        for (int i = 1; i < 3; ++i)
            address[i-1] = set_digit(line[i]);

        virtual_addr = ic = address[0] * 16 + address[1];
        real_addr    = pager.get_real_addr(virtual_addr, ptr);

        block_addr  = real_addr / 16;
        word_addr   = real_addr % 16;
    }

    while (std::getline(file, line)) 
    {
        if (line.length() != 4)
            reading_error("Error, must be 4 bytes");

        line[2] = set_digit(line[2]);
        line[3] = set_digit(line[3]);

        memory[block_addr][word_addr].set_bytes((int)line[0], (int)line[1], (int)line[2], (int)line[3]);

        word_addr++;
        virtual_addr++;

        if(word_addr >= 16)
        {
            real_addr   = pager.get_real_addr(virtual_addr, ptr);

            block_addr  = real_addr / 16;
            word_addr   = real_addr % 16;
        }
    }

    return ic;
}

void ProgramReader::reading_error(const char *message)
{
    file.close();       
    perror(message);
    exit(1);
}

Memory& ProgramReader::get_memory()
{
    return memory;
}