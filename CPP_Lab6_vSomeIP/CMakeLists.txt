cmake_minimum_required(VERSION 3.13)
project(vSomeIP_Capslock_Client)

# 1. Standard C++ 17 requirement
set(CMAKE_CXX_STANDARD 17)

# 2. Find necessary packages
find_package(Threads REQUIRED)
find_package(vsomeip3 REQUIRED)

# 3. Include directories (Standard vsomeip paths on your PC)
include_directories(${VSOMEIP_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 4. Define the executable
add_executable(hello_world_client 
    hello_world_client_main.cpp
)

# 5. Link libraries
# We link vsomeip3 and Threads. 
# Note: If you use the X11 keyboard check, add 'X11' to this list.
target_link_libraries(hello_world_client 
    PRIVATE 
    vsomeip3 
    Threads::Threads
)