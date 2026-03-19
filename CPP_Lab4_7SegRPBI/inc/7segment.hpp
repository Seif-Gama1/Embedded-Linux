#pragma once

#include "GPIO.hpp"
#include "Istream.hpp"
#include "Ostream.hpp"

#include <array>
#include <memory>

class SevenSeg final: public Istream, public Ostream{
    private:
        Gpio a;
        Gpio b;
        Gpio c;
        Gpio d;
        Gpio e;
        Gpio f;
        Gpio g;
    public:
        SevenSeg();
        ~SevenSeg();
        void writeDigit(int digit) override;
        void turnOffAll();
};
