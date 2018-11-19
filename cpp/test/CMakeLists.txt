
include_directories(
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/src"
    )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

add_executable("tests_${PROJECT_NAME}"
    "${PROJECT_SOURCE_DIR}/src/alist.cpp"
    "${PROJECT_SOURCE_DIR}/src/beliefprop.cpp"
    "${PROJECT_SOURCE_DIR}/test/test.cpp"
    "${PROJECT_SOURCE_DIR}/test/test_alist.cpp"
    )
