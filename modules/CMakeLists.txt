set(CMAKE_FOLDER modules)

set(cmake_juce_utils "${JUCE_DIR}/JUCEUtils.cmake")

if(NOT EXISTS "${cmake_juce_utils}")
    message(FATAL_ERROR "Could not locate juce cmake utilities file: '${cmake_juce_utils}'")
endif()
message(STATUS "CMake Juce Utilities File: ${cmake_juce_utils}")
include("${cmake_juce_utils}")

cmake_dependent_option(JUCE_ENABLE_MODULE_SOURCE_GROUPS
    "Show all module sources in IDE projects" OFF
    "NOT JUCE_MODULES_ONLY" OFF)


juce_add_modules(
    ALIAS_NAMESPACE openaudio
    openaudio.core
)

#add_subdirectory(patterns)
add_subdirectory(openaudio.config)
add_subdirectory(openaudio.eq)

#openaudio_add_modules(list_of_modules
#)

