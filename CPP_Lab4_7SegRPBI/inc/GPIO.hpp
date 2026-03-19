#ifndef GPIO_H_
#define GPIO_H_

#include <string>

class Gpio {
private:
    int pinNumber;
    int valueFd;
    int dirFd;

    static int exportFd;
    static int unexportFd;
    static bool opened;

    static void open_ExportFds();
    void exportPin();
    void unexportPin();
    void open_Dir_Val_Fds();
    void close_Dir_Val_Fds();

public:
    Gpio(int pin);
    ~Gpio();

    void setDirection(const char* dir);
    void setValue(int v);
    int  getValue();

    // no copy
    Gpio(const Gpio&) = delete;
    Gpio& operator=(const Gpio&) = delete;

	// just move
    Gpio(Gpio&& other) ;
    Gpio& operator=(Gpio&& other) ;

};

#endif