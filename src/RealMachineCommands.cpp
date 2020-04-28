#include "RealMachine.h"

// Write from memory to register: WAxy WBxy
void RealMachine::writeToMemory(RegisterType registerType, int memoryAddress)
{// NUSETINS SI REIKSME I KAZKOKIA KITA
    switch(registerType)
    {
        case RegisterType::RA:
            //memory[memoryAddress/16][memoryAddress%16] = ra.get_value();
            break;
        case RegisterType::RB:
            //memory[memoryAddress/16][memoryAddress%16] = rb.get_value();
            break;
        default:
            throw "Exception which needs to be implemented; Unknown register\n";
            break;
    }
}

// Load from memory to register: LAxy LBxy
void RealMachine::loadFromMemory(RegisterType registerType, int memoryAddress)
{// NUSETINS SI REIKSME I KAZKOKIA KITA
    switch(registerType)
    {
        case RegisterType::RA:
            //ra.set_value(memory[memoryAddress/16][memoryAddress%16].get_int());
            break;
        case RegisterType::RB:
            //rb.set_value(memory[memoryAddress/16][memoryAddress%16].get_int());
            break;
        default:
            throw "Exception which needs to be implemented; Unknown register\n";
            break;
    }
}

// Do arithmethic commands: ADDX, SUBX, DIVX, MULX
void RealMachine::arithmethicCommand(ArithmeticCommand arithmeticCommand)
{
    switch(arithmeticCommand)
    {
        case ArithmeticCommand::ADD:
            ra.set_value(ra.get_value() + rb.get_value());
            break;
        case ArithmeticCommand::SUB:
            ra.set_value(ra.get_value() - rb.get_value());
            break;
        case ArithmeticCommand::MUL:
            ra.set_value(ra.get_value() * rb.get_value());
            break;
        case ArithmeticCommand::DIV:
            ra.set_value(ra.get_value() / rb.get_value());
            break;
        default:
            throw "Exception which needs to be implemented; Unknown command\n";
            break;
    }
}

// Do compare: CMPX
void RealMachine::compareRegisters()
{
    if (ra.get_value() == rb.get_value())
        sf.set_status(0);
    else if (ra.get_value() > rb.get_value())
        sf.set_status(1);
    else
        sf.set_status(2);     
}

// Jumps: JPxy, JExy, JNxy, JGxy
void RealMachine::jumpToAddress(int memoryAddress, JumpType jumpType)
{
    switch(jumpType)
    {
        case JumpType::ALWAYS:
            ic.set_value(memoryAddress);
            break;
        case JumpType::IF_EQUAL:
            if (sf.get_status() == 0)
                ic.set_value(memoryAddress);
            break;
        case JumpType::IF_NOT_EQUAL:
            if (sf.get_status() != 0)
                ic.set_value(memoryAddress);
            break;
        case JumpType::IF_GREATER:
            if (sf.get_status() == 1)
                ic.set_value(memoryAddress);
            break;
        default:
            throw "Exception which needs to be implemented; Unknown jumptype\n";
            break;
    }
}

// Read word from input device: INxy, FRxy
void RealMachine::readWord(int memoryAddress, bool fromFile)
{
    if (fromFile)
    {
        char word[WORD_LENGTH] = {0, 0, 0, 0};
        int fd = rb.get_value();

#if _WIN32 || _WIN64
        FILE * file = _fdopen(fd, "r");
#elif __APPLE__
        FILE * file = fdopen(fd, "r");
#endif
        int a;
        fscanf(file, "%d", &a);

        //memory[memoryAddress/16][memoryAddress%16] = a;
        /*_read( fd, word, WORD_LENGTH);

        memory[memoryAddress/16][memoryAddress%16].set_bytes(word[0], word[1], word[2], word[3]);*/
    }
    else
    {
        /*if (std::cin.peek() == '$')
        {
            Word word;
            char sym;
            int index = 0;

            // "Eat" the dollar sign
            std::cin.get(sym);

            while(std::cin.get(sym) && index < 4)
            {
                word[index] = sym;
                index++;
            }

            memory[memoryAddress/16][memoryAddress%16] = word;
        }
        else
        {*/
        int num;

        std::cin >> num;
        std::cin.get(); //eat new line

       // memory[memoryAddress/16][memoryAddress%16] = num;
        
    }
}

// Read block form input device: BINx, BFRx
void RealMachine::readBlock(int blockNumber, bool fromFile)
{
    if (fromFile)
    {
        char word[WORD_LENGTH] = {0, 0, 0, 0};
        int fd = rb.get_value();
        int bytesRead = 0;
        int wordIndex = 0;

        //while (((bytesRead = _read( fd, word, WORD_LENGTH)) > 0) && (wordIndex < BLOCK_LENGTH))
        {
        //    memory[blockNumber][wordIndex].set_bytes(word[0], word[1], word[2], word[3]);
            wordIndex++;
        }
    }
    else
    {
        // char start = std::cin.peek();

        // if (start == '$')
        // {
        Word word;
        char sym;
        int byteIndex = 0;
        int wordIndex = 0;

        while (wordIndex < 16)
        {
            byteIndex = 0;
            while(std::cin.get(sym) && byteIndex < 4)
            {
                if(sym == '\n') break;
                word[byteIndex] = sym;
                byteIndex++;
            }
        //    memory[blockNumber][wordIndex] = word;
            wordIndex++;
            
            if (byteIndex < 4)
                break;
        }
        // }
        // else
        // {
        //     int num;
        //     int address = 0;

        //     while(std::cin >> num && address < 16)
        //     {
        //         memory[blockNumber][address] = num;
        //         address++;
        //     }
        // }
    }
}

// Write word to output device: OTxy, FWxy
void RealMachine::writeWord(int wordAddress, bool toFile)
{
    if (toFile)
    {
        int fd = rb;

        std::string toWrite;

       // toWrite = std::to_string(memory[wordAddress/16][wordAddress%16].get_int());
#if _WIN32 || _WIN64
         _write(fd, toWrite.c_str(), toWrite.length());
#elif __APPLE__
        write(fd, toWrite.c_str(), toWrite.length());
#endif
    }
    else
    {
        
        int number;// = memory[wordAddress/16][wordAddress%16].get_int();

        std::cout << number << " " << std::endl;

    }
}

// Write block to output device: BOTx, BFWx
void RealMachine::writeBlock(int blockNumber, bool toFile)
{
    int address = 0;
    uint8_t symbol = 0;

    if (toFile)
    {
        int fd = rb;
        std::string toWrite;

        while(address < 16)
        {
            toWrite = "";
            for (int i = 0; i < 4; ++i)
            {
             //   symbol = memory[blockNumber][address][i];
                if(symbol == 0) break;
                toWrite.push_back(symbol);
            }
#if _WIN32 || _WIN64
            _write(fd, toWrite.c_str(), toWrite.length());
#elif __APPLE__
             write(fd, toWrite.c_str(), toWrite.length());
#endif
            if(symbol == 0) break;
            address++;
        }
    }
    else
    {
        while(address < 16)
        {
            for (int i = 0; i < 4; ++i)
            {
            //    symbol = memory[blockNumber][address][i];
                if(symbol == 0) break;
                std::cout << (char)symbol;
            }
            if(symbol == 0) break;
            address++;
        }
    }
}

// Open/create file: FOxy
void RealMachine::openFile(int memoryAddressOfPath)
{
    std::string path;
    int pathAddress = memoryAddressOfPath;
    int byteIndex = 0;

    char symbol;// = memory[pathAddress/16][pathAddress%16][byteIndex];
    while(symbol != 0)
    {
        path.push_back(symbol);
        
        byteIndex++;
        if(byteIndex >= 4){
            byteIndex = 0;
            pathAddress++;
        }

         //symbol = memory[pathAddress/16][pathAddress%16][byteIndex];
    }
#if _WIN32 || _WIN64
    int file = _open(path.c_str(), _O_CREAT | _O_RDWR, S_IREAD | _S_IWRITE);
#elif __APPLE__
    int file = open(path.c_str(), O_CREAT | O_RDWR, S_IREAD | S_IWRITE);
#endif
    //Store file descriptor in RB
    rb = file;

}

// Close file: FCLS
void RealMachine::closeFile()
{
    //FILE* file = fdopen(rb, "rw");
    //fclose(file);
#if _WIN32 || _WIN64
    _close(rb);
#elif __APPLE__
    close(rb);
#endif
}

// Delete file: FDxy
void RealMachine::deleteFile(int memoryAddressOfPath)
{
    std::string path;
    int pathAddress = memoryAddressOfPath;
    int byteIndex = 0;

    char symbol;// = memory[pathAddress/16][pathAddress%16][byteIndex];
    while(symbol != 0)
    {
        path.push_back(symbol);
        
        byteIndex++;
        if(byteIndex >= 4){
            byteIndex = 0;
            pathAddress++;
        }

        //symbol = memory[pathAddress/16][pathAddress%16][byteIndex];
    }

    remove(path.c_str());
}

// Stop program: HALT
void RealMachine::stopProgram()
{
    running = false;
}