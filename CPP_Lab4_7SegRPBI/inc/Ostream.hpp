#pragma once

#include "Stream.hpp"

class Ostream : virtual public Stream {
    private:
    /* data */
    public:
        Ostream();
        virtual ~Ostream();
        virtual void writeDigit(int digit) = 0;
        // virtual Stream& operator<<(int &digit) = 0;
};