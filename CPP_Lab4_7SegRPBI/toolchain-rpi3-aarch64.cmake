# Target system
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Cross compilers
set(CMAKE_C_COMPILER   /home/seif/x-tools/aarch64-rpi3-linux-gnu/bin/aarch64-rpi3-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER /home/seif/x-tools/aarch64-rpi3-linux-gnu/bin/aarch64-rpi3-linux-gnu-g++)

# Optional: sysroot (recommended if you have one)
# set(CMAKE_SYSROOT /path/to/rpi/sysroot)

# Where CMake looks for libraries/headers
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)