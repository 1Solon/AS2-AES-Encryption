cmake_minimum_required(VERSION 3.10.2)

# You can edit below to change the name of the compiled executable
project(myProgram)

set(CMAKE_C_STANDARD 11) # Using C11 standard, you can change this as needed
set(CMAKE_C_STANDARD_REQUIRED ON)

# Remove for compiler-specific features
set(CMAKE_C_EXTENSIONS OFF)

string(APPEND CMAKE_C_FLAGS " -Wall") # Compiler warnings
string(APPEND CMAKE_C_FLAGS " -pedantic")
string(APPEND CMAKE_C_FLAGS " -Werror") # Treat warnings as errors, disable if you don't like this

# clangd completion, untested but should work
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR})
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.c") # Change to .c for C files, you can change this to .cpp for C++ files

# Set the output directory for the build executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

add_executable(${PROJECT_NAME} ${SOURCES})

# Set the output file extension to .exe
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".exe")