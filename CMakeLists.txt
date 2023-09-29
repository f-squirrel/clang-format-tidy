cmake_minimum_required(VERSION 3.10.2)

project(a.out)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Remove for compiler-specific features
set(CMAKE_CXX_EXTENSIONS OFF)

string(APPEND CMAKE_CXX_FLAGS " -Wall")
string(APPEND CMAKE_CXX_FLAGS " -Wbuiltin-macro-redefined")
string(APPEND CMAKE_CXX_FLAGS " -pedantic")
string(APPEND CMAKE_CXX_FLAGS " -Werror")

# clangd completion
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR})
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/*.cpp")

message (SRC: ${SOURCES})

add_executable(${PROJECT_NAME} ${SOURCES})


# Find clang-format
find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format)

# Gather all source files from the root directory recursively
file(GLOB_RECURSE ALL_SOURCE_FILES
    *.cpp
    *.cc
    *.c++
    *.c
    *.C
    *.h
    *.hpp
    *.hxx
)

# Exclude files in the build directory
list(FILTER ALL_SOURCE_FILES EXCLUDE REGEX "^${CMAKE_BINARY_DIR}.*")

# Create custom target to run clang-format
if(CLANG_FORMAT_EXECUTABLE)
    add_custom_target(
        clang-format
        COMMAND ${CLANG_FORMAT_EXECUTABLE} -i -style=file ${ALL_SOURCE_FILES}
        COMMENT "Running clang-format"
    )
else()
    message("clang-format not found! Target 'clang-format' will not be available.")
endif()


# Create custom target to check clang-format
if(CLANG_FORMAT_EXECUTABLE)
    add_custom_target(
        check-clang-format
        COMMAND ${CLANG_FORMAT_EXECUTABLE} -style=file -Werror --dry-run ${ALL_SOURCE_FILES}
        COMMENT "Checking code format with clang-format"
    )
else()
    message("clang-format not found! Target 'check-clang-format' will not be available.")
endif()


# Find clang-tidy
find_program(CLANG_TIDY_EXECUTABLE NAMES clang-tidy)

# Create custom target to run clang-tidy
if(CLANG_TIDY_EXECUTABLE)
    add_custom_target(
        clang-tidy
        COMMAND ${CLANG_TIDY_EXECUTABLE} -p=${CMAKE_BINARY_DIR} ${ALL_SOURCE_FILES}
        COMMENT "Running clang-tidy"
    )
else()
    message("clang-tidy not found! Target 'clang-tidy' will not be available.")
endif()

# Create custom target to check clang-tidy
if(CLANG_TIDY_EXECUTABLE)
    add_custom_target(
        check-clang-tidy
        COMMAND ${CLANG_TIDY_EXECUTABLE} -p=${CMAKE_BINARY_DIR} --warnings-as-errors=* ${ALL_SOURCE_FILES}
        COMMENT "Checking code quality with clang-tidy"
    )
else()
    message("clang-tidy not found! Target 'check-clang-tidy' will not be available.")
endif()