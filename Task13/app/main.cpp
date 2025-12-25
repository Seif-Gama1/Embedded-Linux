#include <iostream>
#include "7segment.hpp"
#include "IOstream.hpp"

int main()
{
    Istream input;   // input source
    SevenSeg display;       // output sink

    int digit = input.readDigit();
    display.writeDigit(digit);

    return 0;
}
