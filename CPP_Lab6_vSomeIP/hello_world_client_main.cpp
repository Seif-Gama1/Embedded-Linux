// Copyright (C) 2015-2017 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
#include <csignal>
#endif
#include <vsomeip/vsomeip.hpp>
#include "hello_world_client.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <cstring>


#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
hello_world_client *hw_cl_ptr(nullptr);
    void handle_signal(int _signal) {
        if (hw_cl_ptr != nullptr &&
                (_signal == SIGINT || _signal == SIGTERM))
            hw_cl_ptr->stop();
    }
#endif

#define CAPS_PATH "/sys/class/leds/input3::capslock/brightness"


bool is_capslock_on(){
    int fd = open(CAPS_PATH, O_RDONLY);

    char c;
    read(fd, &c, 1);
    close(fd);
    return c == '1';
}

int main(int argc, char **argv)
{
    hello_world_client hw_cl;
    
    if (hw_cl.init()) {
        // 1. Start vsomeip in a background thread so it doesn't block main
        std::thread v_thread([&hw_cl]() {
            hw_cl.start();
        });

        // 2. Your custom loop runs here on the main thread
        bool running = true;
        bool last_state = false;
        
        while(running) {
            bool current_state = is_capslock_on();
            
            // Only proceed if the state is DIFFERENT than it was 100ms ago
            if (hw_cl.is_available() && (current_state != last_state)) {
                hw_cl.send_led_event(current_state);
                last_state = current_state; // Update the memory
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        v_thread.join();
        return 0;
    } else {
        return 1;
    }
}