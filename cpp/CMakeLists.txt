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

configure_file("${PROJECT_SOURCE_DIR}/ldpc-codes-wifi/H_n648-z27-r1_2.alist" "${PROJECT_BINARY_DIR_DIR}" COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/ldpc-codes-wifi/H_n648-z27-r2_3.alist" "${PROJECT_BINARY_DIR_DIR}" COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/ldpc-codes-wifi/H_n648-z27-r3_4.alist" "${PROJECT_BINARY_DIR_DIR}" COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/ldpc-codes-wifi/H_n648-z27-r5_6.alist" "${PROJECT_BINARY_DIR_DIR}" COPYONLY)

# Compile the tests
add_subdirectory(test)

# Compile the source
add_subdirectory(src)

