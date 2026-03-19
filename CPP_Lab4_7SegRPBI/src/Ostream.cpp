#include <Ostream.hpp>
#include <iostream>


Ostream::Ostream(){
    std::cout << "OStream Constructor\n";
}

Ostream::~Ostream(){
    std::cout << "OStream Destructor\n";
}