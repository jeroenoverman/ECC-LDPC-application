cmake_minimum_required(VERSION 3.6)

set(PROJECT_NAME "ldpc")

set (CMAKE_CXX_STANDARD 11)

# The default C Flags
set(CMAKE_CXX_FLAGS
"${CMAKE_CXX_FLAGS} \
-std=c++11 \
-O0 \
-Wall \
-g \
"
)

# Compile the tests
add_subdirectory(test)

# Compile the source
#add_subdirectory(src)

