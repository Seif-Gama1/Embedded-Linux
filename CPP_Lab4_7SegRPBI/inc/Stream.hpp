#pragma once

class Stream {
    private:
    /* data */
    public:
        Stream();
        virtual ~Stream();
        // virtual int readDigit() = 0;
        // virtual void writeDigit(int digit) = 0;

        // virtual Stream& operator>>(int &digit) = 0; // input
        // virtual Stream& operator<<(int digit) = 0;  // output
};