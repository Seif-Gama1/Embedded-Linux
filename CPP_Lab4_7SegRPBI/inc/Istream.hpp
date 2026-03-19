#pragma once

#include "Stream.hpp"

class Istream : virtual public Stream {
    private:
    /* data */
    public:
        Istream();
        virtual ~Istream();
        // virtual Stream& operator>>(int &digit) = 0;
        int readDigit();
};