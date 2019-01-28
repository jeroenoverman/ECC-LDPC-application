
include_directories(
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_BINARY_DIR}/include"
    )

#set(ELF_FILE ${PROJECT_NAME}.elf)
set(ELF_FILE ${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

add_executable(${ELF_FILE}
    "${PROJECT_SOURCE_DIR}/src/main.cpp"
    "${PROJECT_SOURCE_DIR}/src/alist.cpp"
    "${PROJECT_SOURCE_DIR}/src/LDPC_app_base.cpp"
    "${PROJECT_SOURCE_DIR}/src/LDPC_beliefprop.cpp"
    "${PROJECT_SOURCE_DIR}/src/LDPC_encode.cpp"
    "${PROJECT_SOURCE_DIR}/src/bpsk.cpp"
    "${PROJECT_SOURCE_DIR}/src/awgn.cpp"
    "${SOURCE_FILES}"
    )
