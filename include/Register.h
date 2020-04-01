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

    ~Register()
    {

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

    bool check_status()
    {
        return status;
    }

    ~Flag()
    {
        
    }
};