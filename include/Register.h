#pragma once

#include <cstdint>
#include "Word.h"

#include "Word.h"

class Register
{
private:
    Word word;
public:
    void set_value(unsigned int value)
    {
        this->word.set_int(value);
    }

    int get_value()
    {
        return this->word.get_int();
    }
};

class Flag{
private:
    uint8_t status;
public:
    Flag()
    {
        this->status = false;
    }

    bool get_status()
    {
        return status;
    }

    void set_status(uint8_t _status)
    {
        status = _status;
    }

    ~Flag()
    {
        
    }
};