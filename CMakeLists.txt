cmake_minimum_required(VERSION 3.20)

project(fast-csv LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_definitions(
    EXAMPLE_DATA_DIR="${CMAKE_SOURCE_DIR}/src/practice/csv"
)

add_executable(example-1
    src/examples/example-1.cpp
)

add_executable(example-2
    src/examples/example-2.cpp
)

add_executable(practice-1
    src/practice/practice-1.cpp
)

add_executable(practice-2
    src/practice/practice-2.cpp
)

add_executable(example-3
    src/examples/example-3.cpp
)

add_executable(practice-3
    src/practice/practice-3.cpp
)

add_executable(practice-4
    src/practice/practice-4.cpp
)

add_executable(practice-5
    src/practice/practice-5.cpp
)