cmake_minimum_required(VERSION 3.28)
project(8051-simulator LANGUAGES CXX)

# C++23 modules
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API TRUE)
set(CMAKE_CXX_MODULE_CACHE_DIR "${CMAKE_BINARY_DIR}/module-cache")

# Compilers
if (MSVC)
    add_compile_options(/std:c++latest)
else()
    add_compile_options(-std=c++2b)
endif()

# Clang dependency scanner fix
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    find_program(CLANG_SCAN_DEPS_EXECUTABLE NAMES clang-scan-deps clang-scan-deps-18)
    if (CLANG_SCAN_DEPS_EXECUTABLE)
        set(CMAKE_CXX_SCAN_FOR_MODULES_TOOL "${CLANG_SCAN_DEPS_EXECUTABLE}")
        message(STATUS "✅ Found clang-scan-deps: ${CLANG_SCAN_DEPS_EXECUTABLE}")
    else()
        message(WARNING "⚠️ clang-scan-deps not found, module dependency scanning will fail!")
    endif()
endif()

# Catch2
find_package(Catch2 3 REQUIRED)

if (EXISTS "/usr/include/catch2/catch_test_macros.hpp")
    include_directories("/usr/include")
endif()

# Project module liblary
add_library(8051_modules STATIC)

# Modules
target_sources(8051_modules
    PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
            src/cpu.cppm
            src/registers.cppm
            src/memory.cppm
            src/instruction.cppm
            src/io.cppm
            src/system.cppm
)

# Settings
set_target_properties(8051_modules PROPERTIES
    LINKER_LANGUAGE CXX
)

# Main app
add_executable(8051-simulator
    src/main.cpp
)

target_link_libraries(8051-simulator
    PRIVATE
        8051_modules
)

# Tests
add_executable(8051-simulator-tests
    tests/test_system.cpp
    tests/test_cpu.cpp
    tests/test_memory.cpp
    tests/test_register8.cpp
    tests/test_register16.cpp
    tests/test_flag_register.cpp
)

target_link_libraries(8051-simulator-tests
    PRIVATE
        8051_modules
        Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(8051-simulator-tests)

# Info
message(STATUS "-----------------------------------------------")
message(STATUS "Project:   8051-simulator")
message(STATUS "C++:       ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Modules:   ENABLED")
message(STATUS "Build dir: ${CMAKE_BINARY_DIR}")
message(STATUS "-----------------------------------------------")
