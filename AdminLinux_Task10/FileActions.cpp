#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <vector>

class  FileActions {
    private:
        int *fd_;
        int*& fdRef_;
        std::vector<std::pair<std::string, int>> actions_;
    public:
    
    FileActions(const std::string& filename)
        :   fd_(new int(-1)),
            fdRef_(fd_),
            actions_() /* init vector using default constructor */
    {
        *fd_ = open(filename.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        if (*fd_ == -1) {
            std::cout << "Error opening file: " << filename << std::endl;
        }
    }
    
    FileActions(const FileActions& other)    
        : fd_(other.fd_), 
        fdRef_(fd_),              
        actions_(other.actions_)  // vector copies fine
    {
    }

    ~FileActions(){
        if (*fd_ != -1) {
            close(*fd_);
            *fd_ = -1;
            std::cout << "Closed the file descriptor" << std::endl;
        }
        actions_.clear();  
    }

    void registerActions(std::initializer_list<std::pair<std::string,int>> newActions) {
        for (const auto& c : newActions) {
            actions_.push_back(c);
            std::cout<< "Registered action: " << c.first << " with size " << c.second << std::endl;
        }
    }

    // void executeActions(std::string& data, size_t size){
    void executeActions(std::string& data, char* buffer){
        for (const auto& action : actions_) {
            if (action.first == "write") {
                ssize_t bytesWritten = write(*fd_, data.c_str(), action.second);
                if (bytesWritten == -1) {
                    std::cout << "Error writing to file" << std::endl;
                } else {
                    std::cout << "Wrote " << bytesWritten << " bytes to file" << std::endl;
                }
            } else if (action.first == "read") {
                off_t newPos = lseek(*fd_, 0, SEEK_SET);  // first seek to beginning
                if (newPos == -1) {
                    std::cout << "Error seeking in file" << std::endl;
                } else {
                    std::cout << "Seeked to position " << newPos << std::endl;
                }
                
                ssize_t bytesRead = read(*fd_, buffer, action.second);
                if (bytesRead == -1) {
                    std::cout << "Error reading from file" << std::endl;
                } else {
                    buffer[bytesRead] = '\0';
                    std::cout << "Read " << bytesRead << " bytes: " << buffer << std::endl;
                }
            } else if (action.first == "close") {
                if (*fd_ != -1) {
                    close(*fd_);
                    *fd_ = -1;
                    std::cout << "Closed the file descriptor" << std::endl;
                }
            } else {
                std::cout << "Unknown action: " << action.first << std::endl;
            }
        }
    }
};

int main(void){
    FileActions fa("testfile.txt");
    fa.registerActions({ {"write", 18}, {"read", 15}, {"close", 0} });
    char buffer[21]; // Allocate buffer for reading
    std::string data = "some data to write";
    fa.executeActions(data, buffer);
    for(int i=0; i<21; i++){
        buffer[i] = 0;
    }
    return 0;
}