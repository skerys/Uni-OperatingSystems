#include <iostream>

#include "Word.h"

Block::Block()
{
    for (unsigned int i = 0; i < BLOCK_LENGTH; i++)
    {
        words[i] = Word w(new Word());
    }
}

Word Block::get_word(unsigned int position)
{
    if ((position >= 0) && (position < BLOCK_LENGTH))
    {
        return words[position];
    }
    throw "Bad block position";
}

bool Block::set_word(unsigned int position, Word word)
{
    if ((position >= 0) && (position < BLOCK_LENGTH))
    {
        words[position] = word;
        return true;
    }
    return false;
}

Block::~Block()
{
    words.clear();
}