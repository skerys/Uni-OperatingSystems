#pragma once
#include <cstdint>
#include <string>
#include <stdio.h>
#include <cassert>

#define WORD_LENGTH 4

struct Word{
private:
    uint8_t bytes[WORD_LENGTH];
public:
    Word(){}

    uint8_t get_byte(int index){
        assert(index >=0 && index < WORD_LENGTH);
        return bytes[index];

    }

    void set_byte(int index, uint8_t value){
        assert(index >=0 && index < WORD_LENGTH);
        bytes[index] = value;
    }

    int get_int()
    {
        return (int)bytes[0] << 24 |
                    bytes[1] << 16 |
                    bytes[2] << 8  |
                    bytes[3];
    }

    void set_int(int value){
        bytes[0] = (value >> 24) & 0xFF;
        bytes[1] = (value >> 16) & 0xFF;
        bytes[2] = (value >> 8) & 0xFF;
        bytes[3] = value & 0xFF;
    }

    void print_bytes(){
        printf("Bytes: %X %X %X %X\n", bytes[0], bytes[1], bytes[2], bytes[3]);
    }
};