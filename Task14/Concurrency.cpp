#include <unistd.h>
#include <fcntl.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <cstring>

#define CAPS_PATH "/sys/class/leds/input3::capslock/brightness"

std::mutex mtx;
std::condition_variable cv;
bool caps_clicked = false;
std::atomic<bool> running{true};

bool is_capslock_on(){
    int fd = open(CAPS_PATH, O_RDONLY);

    char c;
    read(fd, &c, 1);
    close(fd);
    return c == '1';
}

void caps_thread(){
    bool prev = is_capslock_on();
    bool curr = false;

    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        curr = is_capslock_on();

        if (prev != curr){
            {
                std::lock_guard<std::mutex> lock(mtx);
                caps_clicked = true;
            }
            cv.notify_one();
        }
        prev = curr;
    }
}

void write_therad(int fd){
    char* msg = "Capslock is clicked\n";
    while (running) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return caps_clicked || !running; });

        write(fd, msg, strlen(msg));
        
        caps_clicked = false;
    }
}

int main(){
    int fd = open("capslog.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
    std::thread t1(caps_thread);
    std::thread t2(write_therad, fd);
    std::this_thread::sleep_for(std::chrono::seconds(30));
    running = false;
    cv.notify_all();

    t1.join();
    t2.join();
    close(fd);
}
