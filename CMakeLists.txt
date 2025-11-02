cmake_minimum_required(VERSION 3.28)
project(8051-simulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/std:c++latest)
else()
    add_compile_options(-std=c++2b)
endif()

find_package(Catch2 REQUIRED)

add_executable(8051-simulator
    src/main.cpp
    src/cpu.cppm
    src/registers/register8.cppm
    src/registers/register16.cppm
    src/registers/flag_register.cppm
    src/memory.cppm
    src/instruction.cppm
    src/io.cppm
    src/system.cppm
)

add_executable(8051-simulator-tests
    tests/test_cpu.cpp
    tests/test_register.cpp
    tests/test_flag_register.cpp
    src/cpu.cppm
    src/registers/register8.cppm
    src/registers/register16.cppm
    src/registers/flag_register.cppm
)

target_link_libraries(8051-simulator-tests PRIVATE Catch2::Catch2WithMain)