
include_directories(
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/src"
    )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

configure_file("${PROJECT_SOURCE_DIR}/ldpc-codes-wifi/H_n648-z27-r1_2.alist" "${PROJECT_BINARY_DIR_DIR}" COPYONLY)

add_executable("test_alist"
    "${PROJECT_SOURCE_DIR}/test/test_alist.cpp"
    "${PROJECT_SOURCE_DIR}/test/test.cpp"
    "${PROJECT_SOURCE_DIR}/src/alist.cpp"
    )

add_executable("test_ldpc_beliefprop"
    "${PROJECT_SOURCE_DIR}/test/test_ldpc_beliefprop.cpp"
    "${PROJECT_SOURCE_DIR}/test/test.cpp"
    "${PROJECT_SOURCE_DIR}/src/alist.cpp"
    "${PROJECT_SOURCE_DIR}/src/beliefprop.cpp"
    "${PROJECT_SOURCE_DIR}/src/LDPC_encode.cpp"
    "${PROJECT_SOURCE_DIR}/src/bpsk.cpp"
    "${PROJECT_SOURCE_DIR}/src/awgn.cpp"
    )

add_executable("test_bpsk"
    "${PROJECT_SOURCE_DIR}/test/test_bpsk.cpp"
    "${PROJECT_SOURCE_DIR}/src/bpsk.cpp"
    "${PROJECT_SOURCE_DIR}/test/test.cpp"
    )

add_executable("test_awgn"
    "${PROJECT_SOURCE_DIR}/test/test_awgn.cpp"
    "${PROJECT_SOURCE_DIR}/src/bpsk.cpp"
    "${PROJECT_SOURCE_DIR}/src/awgn.cpp"
    "${PROJECT_SOURCE_DIR}/test/test.cpp"
    )

add_executable("test_ldpc_encode"
    "${PROJECT_SOURCE_DIR}/test/test_ldpc_encode.cpp"
    "${PROJECT_SOURCE_DIR}/test/test.cpp"
    "${PROJECT_SOURCE_DIR}/src/alist.cpp"
    "${PROJECT_SOURCE_DIR}/src/LDPC_encode.cpp"
    )
