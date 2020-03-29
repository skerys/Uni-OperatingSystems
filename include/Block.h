#ifndef BLOCK_H
#define BLOCK_H

#define BLOCK_LENGTH 16

#include <memory>
#include <vector>

#include "Word.h"

class Block
{
private:
    std::array<Word, BLOCK_LENGTH> words;
public:
    Block();
    Word get_word(unsigned int);
    bool set_word(unsigned int, Word);
    ~Block();
};

#endif