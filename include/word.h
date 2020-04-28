#pragma once

#include <cstdint>
#include <string>
#include <stdio.h>
#include <cassert>

#include "GlobalDefines.h"

class Word
{
private:
    uint8_t bytes[WORD_LENGTH];
#if DEBUG_MODE
    bool isInt = false;
#endif
public:
    uint8_t& operator[](int i)
    {
        return get_byte(i);
    }

    void operator=(const int &i)
    {
        set_int(i);
    }

    uint8_t& get_byte(int index)
    {
        assert(index >=0 && index < WORD_LENGTH);
        return bytes[index];
    }

    void set_byte(int index, uint8_t value)
    {
#if DEBUG_MODE
        isInt = false;
#endif
        assert(index >=0 && index < WORD_LENGTH);
        bytes[index] = value;
    }

    void set_bytes(int byte0, int byte1, int byte2, int byte3)
    {
#if DEBUG_MODE
        isInt = false;
#endif
        bytes[0] = byte0;
        bytes[1] = byte1;
        bytes[2] = byte2;
        bytes[3] = byte3;
    }

    int get_int()
    {
        return  (int)bytes[0] << 24 |
                (int)bytes[1] << 16 |
                (int)bytes[2] << 8  |
                (int)bytes[3];
    }

    void set_int(int value)
    {
#if DEBUG_MODE
        isInt = true;
#endif
        bytes[0] = (value >> 24) & 0xFF;
        bytes[1] = (value >> 16) & 0xFF;
        bytes[2] = (value >> 8) & 0xFF;
        bytes[3] = value & 0xFF;
    }

    void print()
    {
#if DEBUG_MODE
        if(isInt)
        {
            printf("%4X ", get_int());
        }
        else
        {
            Word toPrint = *this;

            if(toPrint[2] <= 15){
                toPrint[2] = toPrint[2] >= 10 ? 'A' + toPrint[2] - 10 : '0' + toPrint[2];
            }
            if(toPrint[3] <= 15){
                toPrint[3] = toPrint[3] >= 10 ? 'A' + toPrint[3] - 10 : '0' + toPrint[3];
            }
            printf("%c%c%c%c ", toPrint[0], toPrint[1], toPrint[2], toPrint[3]);
        }
    }
#else
    }
#endif

    void print_bytes()
    {
        printf("Bytes: %X %X %X %X\n", bytes[0], bytes[1], bytes[2], bytes[3]);
    }
};