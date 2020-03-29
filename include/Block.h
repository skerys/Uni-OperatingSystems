#ifndef BLOCK_H
#define BLOCK_H

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
        for (unsigned int i = 0; i < BLOCK_LENGTH; i++)
        {
            words[i] = Word w(new Word());
        }
    }

    Word get_word(unsigned int position)
    {
        if ((position >= 0) && (position < BLOCK_LENGTH))
        {
            return words[position];
        }
        throw "Bad block position";
    }

    bool set_wordset_word(unsigned int position, Word word)
    {
        if ((position >= 0) && (position < BLOCK_LENGTH))
        {
            words[position] = word;
            return true;
        }
        return false;
    }

    ~Block()
    {
        std::fill(words, BLOCK_LENGTH, 0);
    }
};

#endif