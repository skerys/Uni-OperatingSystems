#pragma once

#define BLOCK_LENGTH 16

#include <memory>
#include <vector>

#include "Word.h"

class Block
{
private:
    Word words[BLOCK_LENGTH];
public:
    Block()
    {
        for(int i = 0; i < BLOCK_LENGTH; ++i)
        {
            words[i].set_int(0);
        }
    }

    Word& operator[](int i){
        return get_word(i);
    }

    Word& get_word(unsigned int position)
    {
        if ((position >= 0) && (position < BLOCK_LENGTH))
        {
            return words[position];
        }
        throw "Bad block position";
    }

    bool set_word(unsigned int position, Word word)
    {
        if ((position >= 0) && (position < BLOCK_LENGTH))
        {
            words[position] = word;
            return true;
        }
        return false;
    }

    bool set_int(unsigned int position, unsigned int value)
    {
        if ((position >= 0) && (position < BLOCK_LENGTH))
        {
            words[position].set_int(value);
            return true;
        }
        return false;
    }

    ~Block()
    {
        
    }
};