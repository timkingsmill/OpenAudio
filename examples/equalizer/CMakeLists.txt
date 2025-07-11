cmake_minimum_required(VERSION 3.22)
project(EQUALIZER_EXAMPLE VERSION 0.0.1)

# If you've installed JUCE somehow (via a package manager, 
# or directly using the CMake install target),
# you'll need to tell this project that it 
# depends on the installed copy of JUCE. 
# If you've included
# JUCE directly in your source tree (perhaps as a submodule), you'll need to tell CMake to include
# that subdirectory as part of the build. 



find_package(JUCE CONFIG REQUIRED)  



# DUMP the JUCE_DIR variable to see where CMake is looking for JUCE
message(STATUS "JUCE_DIR: ${JUCE_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "JUCE_MODULES_DIR: ${JUCE_MODULES_DIR}")
message(STATUS "JUCE_CMAKE_UTILS_DIR: ${JUCE_CMAKE_UTILS_DIR}")
message(STATUS "JUCE_BINARY_DIR: ${JUCE_BINARY_DIR}")
message(STATUS "JUCE_INSTALL_DESTINATION: ${JUCE_INSTALL_DESTINATION}")
message(STATUS "JUCE_TOOL_INSTALL_DIR: ${JUCE_TOOL_INSTALL_DIR}")
message(STATUS "JUCEAIDE_PATH: ${JUCEAIDE_PATH}")
message(STATUS "JUCE_GLOBAL_ARA_SDK_PATH: ${JUCE_GLOBAL_ARA_SDK_PATH}")
message(STATUS "JUCE_WEBVIEW2_PACKAGE_LOCATION: ${JUCE_WEBVIEW2_PACKAGE_LOCATION}")
message(STATUS "JUCE_VERSION: ${JUCE_VERSION}")
message(STATUS "JUCE_BUILD_EXTRAS: ${JUCE_BUILD_EXTRAS}")
message(STATUS "JUCE_BUILD_EXAMPLES: ${JUCE_BUILD_EXAMPLES}")
message(STATUS "JUCE_WEBVIEW2_PACKAGE_LOCATION: ${JUCE_WEBVIEW2_PACKAGE_LOCATION}")

###add_subdirectory(JUCE_SOURCE_DIR)