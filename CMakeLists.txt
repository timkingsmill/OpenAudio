cmake_minimum_required(VERSION 3.26.3)

project(OpenAudio VERSION 0.1.0 LANGUAGES C CXX)

include(CMakeDependentOption)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed. Please create a separate build directory and run CMake from there.")
endif()

#add_subdirectory(external)
add_subdirectory(examples)

