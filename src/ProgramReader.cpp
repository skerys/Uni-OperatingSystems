#include <fstream>

#include "ProgramReader.h"

void ProgramReader::set_memory(std::string filename)
{       
    file.open(filename);
    std::string line;

    if (file.is_open()) 
    {
        line = set_datablock();
        set_codeblock(line);
        file.close();
    }
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
            for(int i = 1; i < 5; ++i)
                line[i] = set_digit(line[i]);

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
                memory[address[2]][address[3]].set_int(std::stoi(line, nullptr));

            std::getline(file, line);
        }
    }
    return line;
}

void ProgramReader::set_codeblock(std::string line)
{
    int lineNo = 0;

    if (line != "CODE")
        reading_error("Must be code");

    while (std::getline(file, line)) 
    {
        if (line.length() != 4)
            reading_error("Error, must be 4 bytes");

        line[2] = set_digit(line[2]);
        line[3] = set_digit(line[3]);

        memory[lineNo/16][lineNo%16].set_bytes((int)line[0], (int)line[1], (int)line[2], (int)line[3]);

        lineNo++;
    }
}

void ProgramReader::reading_error(const char *message)
{
    file.close();       
    perror("Error, must be 4 bytes");
    exit(1);
}

Memory& ProgramReader::get_memory()
{
    return memory;
}