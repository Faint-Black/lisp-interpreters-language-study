#-------------------------------------------------------------------------------
# Provided by yours truly; LLM.
# I cannot be bothered with Cmake, i hate it, really.
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.12)
project(lisp-implementation C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


#-------------------------------------------------------------------------------
# 1. Compiler Settings (ANSI C + Warnings)
#-------------------------------------------------------------------------------
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Enable (most) warnings and optimizations
add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wshadow
    -Wno-unused-function
    -O2
)


#-------------------------------------------------------------------------------
# 2. Clang-Tidy Configuration
#-------------------------------------------------------------------------------
find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if(CLANG_TIDY_EXE)
    set(CMAKE_C_CLANG_TIDY 
        ${CLANG_TIDY_EXE} 
        --extra-arg=-std=c90
    )
    message(STATUS "clang-tidy enabled: ${CMAKE_C_CLANG_TIDY}")
else()
    message(WARNING "clang-tidy not found!")
endif()


#-------------------------------------------------------------------------------
# 3. Clang-Format Configuration
#-------------------------------------------------------------------------------
find_program(CLANG_FORMAT_EXE NAMES "clang-format")
if(CLANG_FORMAT_EXE)
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXE}
        -i
        --style=file
        ${CMAKE_SOURCE_DIR}/src/*.c
        ${CMAKE_SOURCE_DIR}/src/include/*.h
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
    message(STATUS "clang-format enabled: ${CLANG_FORMAT_EXE}")
else()
    message(WARNING "clang-format not found!")
endif()


#-------------------------------------------------------------------------------
# 4. Build Source Files
#-------------------------------------------------------------------------------
# Add your source files
file(GLOB_RECURSE SOURCES "src/*.c")
file(GLOB_RECURSE HEADERS "src/include/*.h")

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)
