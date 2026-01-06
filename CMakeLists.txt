cmake_minimum_required(VERSION 4.2.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set C++23 as the default for all targets
set(CMAKE_CXX_STANDARD 23)
# Ensure the compiler supports the specified standard
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
# Disable compiler-specific extensions by default
set(CMAKE_CXX_EXTENSIONS OFF) 

project(OpenAudio VERSION 0.1.0 LANGUAGES C CXX)

include(CMakeDependentOption)

# Add the JUCE libaray to CMAKE_PREFIX_PATH for find_package
set(CMAKE_PREFIX_PATH "/source/OpenAudio/libs/JUCE/install")

find_package(JUCE CONFIG REQUIRED)  

#include(extras/build/CMake/OpenAudioUtils.cmake)
#include(external/extras/build/CMake/CMakeUtils.cmake)


if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed. Please create a separate build directory and run CMake from there.")
endif()

add_subdirectory(modules)
add_subdirectory(examples)

add_subdirectory(applications)
# -----------------------------------------------------------------------------------------------