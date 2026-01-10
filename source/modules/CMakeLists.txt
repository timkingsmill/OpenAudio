set(CMAKE_FOLDER modules)

set(cmake_juce_utils "${JUCE_DIR}/JUCEUtils.cmake")

if(NOT EXISTS "${cmake_juce_utils}")
    message(FATAL_ERROR "Could not locate juce cmake utilities file: '${cmake_juce_utils}'")
endif()
message(STATUS "CMake Juce Utilities File: ${cmake_juce_utils}")
include("${cmake_juce_utils}")

juce_add_modules(
    ALIAS_NAMESPACE openaudio
    openaudio_core
    openaudio_eq
    openaudio_lookandfeel
)


