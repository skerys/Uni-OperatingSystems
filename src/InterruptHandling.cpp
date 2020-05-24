#include "../include/RealMachine.h"


void RealMachine::handle_interrupt()
{   
    switch (si.get_status())
    {
        case 1:
            write_to_memory(RegisterType::RA);
            break;
        case 2: 
            write_to_memory(RegisterType::RB);
            break;
        case 3:
            load_from_memory(RegisterType::RA);
            break;
        case 4:
            load_from_memory(RegisterType::RB);
            break;
        case 5:
            read_word(false);
            break;
        case 6:
            read_block(false);
            break;
        case 7:
            write_word(false);
            break;
        case 8:
            write_block(false);
            break;
        case 9:
            write_word(true);
            break;
        case 10:
            write_block(true);
            break;
        case 11:
            read_word(true);
            break;
        case 12:
            read_block(true);
            break;
        case 13:
            open_file();
            break;
        case 14:
            close_file();
            break;
        case 15:
            delete_file();
        default:
            fprintf(stderr, "SI value too high! Interrupt with code %d not found", si);
    }

    si = 0;
    pi = 0;
    oi = 0;
}

void RealMachine::write_to_memory(RegisterType registerType)
{
    int memoryAddress = pager.get_real_addr(rc, ptr.get_word());
    switch(registerType)
    {
        case RegisterType::RA:
            memory[memoryAddress/16][memoryAddress%16] = ra.get_value();
            break;
        case RegisterType::RB:
            memory[memoryAddress/16][memoryAddress%16] = rb.get_value();
            break;
        default:
            fprintf(stderr,"Unknown register type in write_to_memory\n");
            break;
    }
}

void RealMachine::load_from_memory(RegisterType registerType)
{
    int memoryAddress = pager.get_real_addr(rc, ptr.get_word());
    switch(registerType)
    {
        case RegisterType::RA:
            ra.set_value(memory[memoryAddress/16][memoryAddress%16].get_int());
            break;
        case RegisterType::RB:
            rb.set_value(memory[memoryAddress/16][memoryAddress%16].get_int());
            break;
        default:
            fprintf(stderr,"Unknown register type in load_from_memory\n");
            break;
    }
}

// Read word from input device: INxy, FRxy
void RealMachine::read_word(bool fromFile)
{
    int memoryAddress = pager.get_real_addr(rc, ptr.get_word());
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

        memory[memoryAddress/16][memoryAddress%16] = a;

        if(file == nullptr)
        {
            pi = 5;
            fprintf(stderr, "Incorrect descriptor of the file");
            exit(1);
        }
    }
    else
    {
        int num;

        std::cin >> num;
        std::cin.get(); //eat new line

        memory[memoryAddress/16][memoryAddress%16] = num;      
    }
}

void RealMachine::read_block(bool fromFile)
{
    int blockNumber = pager.get_read_block(rc, ptr.get_word());

    if (fromFile)
    {
        char word[WORD_LENGTH] = {0, 0, 0, 0};
        int fd = rb.get_value();
        int bytesRead = 0;
        int wordIndex = 0;

        while (((bytesRead = _read( fd, word, WORD_LENGTH)) > 0) && (wordIndex < BLOCK_LENGTH))
        {
            memory[blockNumber][wordIndex].set_bytes(word[0], word[1], word[2], word[3]);
            wordIndex++;
        }

        if(bytesRead == -1)
        {
            pi = 5;
            fprintf(stderr, "Incorrect descriptor of the file");
            exit(1);
        }
    }
    else
    {
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
            memory[blockNumber][wordIndex] = word;
            wordIndex++;
            
            if (byteIndex < 4)
                break;
        }
    }
}

void RealMachine::write_word(bool toFile)
{
    int wordAddress = pager.get_real_addr(rc, ptr.get_word());

    if (toFile)
    {
        int fd = rb;

        std::string toWrite;

        toWrite = std::to_string(memory[wordAddress/16][wordAddress%16].get_int());
#if _WIN32 || _WIN64
        int error = _write(fd, toWrite.c_str(), toWrite.length());
#elif __APPLE__
        int error = write(fd, toWrite.c_str(), toWrite.length());
#endif
        if(error == -1)
        {
            pi = 5;
            fprintf(stderr, "Incorrect descriptor of the file");
            exit(1);
        }
    }
    else
    {      
        int number =  memory[wordAddress/16][wordAddress%16].get_int();

        std::cout << number << " " << std::endl;
    }
}

void RealMachine::write_block(bool toFile)
{
    int blockNumber = pager.get_read_block(rc, ptr.get_word());

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
                symbol = memory[blockNumber][address][i];
                if(symbol == 0) break;
                toWrite.push_back(symbol);
            }
#if _WIN32 || _WIN64
            int error = _write(fd, toWrite.c_str(), toWrite.length());
#elif __APPLE__
            int error = write(fd, toWrite.c_str(), toWrite.length());
#endif
            if(symbol == 0) break;
            address++;

            if(error == -1)
            {
                pi = 5;
                fprintf(stderr, "Incorrect descriptor of the file");
                exit(1);
            }
        }
    }
    else
    {
        while(address < 16)
        {
            for (int i = 0; i < 4; ++i)
            {
                symbol = memory[blockNumber][address][i];
                if(symbol == 0) break;
                std::cout << (char)symbol;
            }
            if(symbol == 0) break;
            address++;
        }
    }
}

void RealMachine::open_file()
{
    std::string path;
    int pathAddress = pager.get_real_addr(rc, ptr.get_word());
    int byteIndex = 0;

    char symbol = memory[pathAddress/16][pathAddress%16][byteIndex];
    while(symbol != 0)
    {
        path.push_back(symbol);
        
        byteIndex++;
        if(byteIndex >= 4){
            byteIndex = 0;
            pathAddress++;
        }

         symbol = memory[pathAddress/16][pathAddress%16][byteIndex];
    }
#if _WIN32 || _WIN64
    int file = _open(path.c_str(), _O_CREAT | _O_RDWR, S_IREAD | _S_IWRITE);
#elif __APPLE__
    int file = open(path.c_str(), O_CREAT | O_RDWR, S_IREAD | S_IWRITE);
#endif
    //Store file descriptor in RB
    rb = file;

    if(file == -1)
    {
        pi = 6;
        fprintf(stderr, "File or path not found");
        exit(1);
    }
}

void RealMachine::close_file()
{
#if _WIN32 || _WIN64
    int error = _close(rb);
#elif __APPLE__
    int error = close(rb);
#endif
    if(error == -1)
    {
        pi = 5;
        fprintf(stderr, "Incorrect descriptor of the file");
        exit(1);
    }
}

void RealMachine::delete_file()
{
    std::string path;
    int pathAddress = pager.get_real_addr(rc, ptr.get_word());
    int byteIndex = 0;

    char symbol = memory[pathAddress/16][pathAddress%16][byteIndex];
    while(symbol != 0)
    {
        path.push_back(symbol);
        
        byteIndex++;
        if(byteIndex >= 4){
            byteIndex = 0;
            pathAddress++;
        }

        symbol = memory[pathAddress/16][pathAddress%16][byteIndex];
    }

    int error = remove(path.c_str());

    if(error == -1)
    {
        pi = 6;
        fprintf(stderr, "File or path not found");
        exit(1);
    }
}

void RealMachine::do_timer_interrupt()
{
    write_registers(currentActiveVm);
    int newVm = currentActiveVm + 1;
    while(activeVm[newVm] != true)
    {
        if(++newVm >= VIRTUAL_MACHINE_NUM){
            newVm = 0;
        }
    }
    load_registers(newVm);
    currentActiveVm = newVm;
    ti = 10;
}