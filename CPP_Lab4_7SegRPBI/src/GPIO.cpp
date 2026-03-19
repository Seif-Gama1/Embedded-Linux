#include "GPIO.hpp"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

int Gpio::exportFd = -1;
int Gpio::unexportFd = -1;
bool Gpio::opened = false;


Gpio::Gpio(int pin)
{
	pinNumber = pin;
	valueFd = -1;
	dirFd = -1;
    open_ExportFds();
    exportPin();
    usleep(100000);  // wait 100ms for sysfs to create the gpio pin folder
    open_Dir_Val_Fds();
}

// move constructor
Gpio::Gpio(Gpio&& other)  {
    pinNumber = other.pinNumber;
    valueFd   = other.valueFd;
    dirFd     = other.dirFd;

    other.pinNumber = -1;
    other.valueFd = -1;
    other.dirFd = -1;
}

// move assignment
Gpio& Gpio::operator=(Gpio&& other)  {
    if (this != &other) {
        close_Dir_Val_Fds(); 

        pinNumber = other.pinNumber;
        valueFd   = other.valueFd;
        dirFd     = other.dirFd;

        other.pinNumber = -1; 			 
        other.valueFd = -1;
        other.dirFd = -1;
    }
    return *this;
}

Gpio::~Gpio() {
    printf("Destructor is called");
    close_Dir_Val_Fds();
    unexportPin();
}


void Gpio::setDirection(const char* dir) {
    if (dirFd == -1) {
        std::cout << "dirFd not open for pin " << pinNumber << "\n";
        return;
    }

    lseek(dirFd, 0, SEEK_SET); 	// reset file offset to handle multiple writes
    if (write(dirFd, dir, strlen(dir)) == -1)
        std::cout << "setDirection failed for pin " << pinNumber << "\n";
}

void Gpio::setValue(int v) {
    if (valueFd == -1) {
        std::cout << "valueFd not open for write pin " << pinNumber << "\n";
        return;
    }

    char c = (v ? '1' : '0');
    lseek(valueFd, 0, SEEK_SET); // reset file offset to handle multiple writes
    if (write(valueFd, &c, 1) == -1)
        std::cout << "setValue failed for pin " << pinNumber << "\n";
}

int Gpio::getValue() {
    if (valueFd == -1) {
        std::cout << "valueFd not open for read pin " << pinNumber << "\n";
        return -1;
    }

    char c = '0';
    lseek(valueFd, 0, SEEK_SET); // reset file offset to handle multiple reads
    if (read(valueFd, &c, 1) == -1) {
        std::cout << "getValue failed for pin " << pinNumber<< "\n";
        return -1;
    }
    return (c == '1') ? 1 : 0;
}


void Gpio::open_ExportFds(){
    if(opened) return;

    exportFd = open("/sys/class/gpio/export", O_WRONLY);
    unexportFd = open("/sys/class/gpio/unexport", O_WRONLY);
    if(exportFd == -1){
        std::cout<<"Failed to open export FD \n";
    }
    if(unexportFd == -1){
        std::cout<<"Failed to open unexport FD \n";
    }

    opened = true;
}

void Gpio::exportPin(){
    if(exportFd == -1){
        std::cout<<"exportFd is not even available\n";
        return;
    }

    std::string s = std::to_string(pinNumber);
    if(write(exportFd, s.c_str(), s.size()) == -1){
        std::cout<< "export failed for PinNumber: "<<pinNumber<<"\n";
    }
}

void Gpio::unexportPin(){
    printf("Unexporting GPIO pin");
    if(unexportFd == -1){
        std::cout<<"unexportFd is not even available\n";
        return;
    }

    std::string s = std::to_string(pinNumber);
    if(write(unexportFd, s.c_str(), s.size()) == -1){
        std::cout<< "unexport failed for PinNumber: "<<pinNumber<<"\n";
    }
}


void Gpio::open_Dir_Val_Fds() {
    std::string base = "/sys/class/gpio/gpio" + std::to_string(pinNumber) + "/";
    std::string dirPath = base + "direction";
    std::string valPath = base + "value";

    dirFd = open(dirPath.c_str(), O_WRONLY);
    if (dirFd == -1)
        std::cout<<"Failed to open "<< dirPath <<"\n";

    valueFd = open(valPath.c_str(), O_RDWR);
    if (valueFd == -1)
        std::cout<<"Failed to open "<<valPath << "\n";
}

void Gpio::close_Dir_Val_Fds() {
    if(valueFd != -1){ 
        close(valueFd);
        valueFd = -1; 
    }
    if(dirFd != -1){
        close(dirFd);
        dirFd = -1; 
    }
}

