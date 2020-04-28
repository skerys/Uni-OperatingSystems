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
}