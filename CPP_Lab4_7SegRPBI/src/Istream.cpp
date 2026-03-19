#include <Istream.hpp>
#include <iostream>


Istream::Istream(){
    std::cout << "IStream Constructor\n";
}

Istream::~Istream(){
    std::cout << "IStream Destructor\n";
}

int Istream::readDigit(void){
    int num = -1;
    while (true)
    {
        std::cout << "Enter Number 0~9\n";
        std::cin >> num;
        if (num <= 9 && num >= 0)
        {
            break;
        }
        else
        {
            std::cout << "Invalid Number Retry ..\n";
        }
    }
    return num;
}