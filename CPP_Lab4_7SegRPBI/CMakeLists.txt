cmake_minimum_required(VERSION 3.10)

project(SevenSegment C CXX)

add_library(my_lib
            SHARED 
            src/GPIO.cpp
            src/IOstream.cpp
            src/Istream.cpp
            src/Ostream.cpp
            src/Stream.cpp
            src/7segment.cpp)

target_include_directories(my_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_executable(${PROJECT_NAME} app/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE my_lib)