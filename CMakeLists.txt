cmake_minimum_required(VERSION 3.10)

project(lab1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g")

include_directories(include)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin)

add_library(sequence_lib SHARED
        src/Sequence.cpp
)

add_library(sorter_lib SHARED
        src/ISorter.cpp
)

add_executable(${PROJECT_NAME}
        src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC sequence_lib sorter_lib)

add_executable(${PROJECT_NAME}_tests
        tests/sorter_tests.cpp
)

target_link_libraries(${PROJECT_NAME}_tests PUBLIC sequence_lib sorter_lib)
