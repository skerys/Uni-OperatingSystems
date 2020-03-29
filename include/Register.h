#ifndef REGISTER_H
#ifndef REGISTER_H

#include <cstdint>

class Register
{
private:
    Word word;
public:
    Register(Word word)
    {
        this->word = word;
    }

    bool Register::set_value(unsigned int value)
    {
        this->word.set_int(value);
    }

    int Register::get_value()
    {
        this->word.get_int();
    }

    ~Register();
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
}

#endif