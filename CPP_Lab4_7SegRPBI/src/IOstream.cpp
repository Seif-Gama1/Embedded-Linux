#include <IOstream.hpp>
#include <iostream>

IOstream::IOstream(){
    std::cout << "IOstream Constructor\n";
}

IOstream::~IOstream(){
    std::cout << "IOstream Destructor\n";
}

void IOstream::writeDigit(int digit){
    std::cout << "Digit " << digit << std::endl;
}

int IOstream::readDigit(void){
    int num = -1;
    while (true){
        std::cout << "Enter Number from 0 to 9\n";
        std::cin >> num;
        if (num <= 9 && num >= 0){
            break;
        }
        else{
            std::cout << "Invalid Number Retry ..\n";
        }
    }
    return num;
}