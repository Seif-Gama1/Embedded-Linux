# cmake_minimum_required(VERSION 3.15)

# # CMAKE_BUILD_RPATH:
# # tells the linker to use relative paths for the library search path
# # this is NOT required if we build on the same machine
# # but since we will run on the PI we need to do this
# set(CMAKE_BUILD_RPATH "$ORIGIN/lib")


# project(inheritanceApp CXX)



# add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src ${CMAKE_CURRENT_BINARY_DIR}/lib )

# add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/app/main.cpp)


# target_link_libraries(${PROJECT_NAME} PRIVATE sevneseg)