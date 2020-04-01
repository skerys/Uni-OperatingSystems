#pragma once

#include <cstdint>

class CommandReader{
    static uint16_t combine_two_bytes(uint8_t byteA, uint8_t byteB)
    {
        return (uint16_t)byteA * 0xFF + byteB;
    }
};