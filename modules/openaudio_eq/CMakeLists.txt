project(openaudio.eq VERSION 0.1.0 LANGUAGES C CXX)

add_library(openaudio.eq INTERFACE
)

##juce_add_module(
##    .
##)


# Create the JuceHeader.h for this target.
###juce_generate_juce_header(openaudio.eq)

target_sources(openaudio.eq
    PUBLIC
        source/ParametricEqualiserEditor.cpp
        source/ParametricEqualiserProcessor.cpp
    PUBLIC
        FILE_SET myHeaders
            TYPE HEADERS
            BASE_DIRS
                include
            FILES
                include/ParametricEqualiserProcessor.h
                include/ParametricEqualiserEditor.h
)


#get_target_property(interface_sources_list openaudio.eq INTERFACE_SOURCES)
#message(STATUS "--------------------------------")
#message(STATUS "InterfaceSources for XXXXXXXXXXXXXXXXXXopenaudio.eq: ${interface_sources_list}")
#message(STATUS "--------------------------------")

get_target_property(target_sources_list openaudio.eq SOURCES)
message(STATUS " --- Sources for openaudio.eq: ${target_sources_list}")

##get_target_property(ExecutablePath openaudio.eq SOURCE_DIR)
##message(STATUS "Target Path for openaudio.eq: ${ExecutablePath}")

source_group(
    TREE "${CMAKE_CURRENT_SOURCE_DIR}/source"
    PREFIX "openaudio.eq Source Files"
    FILES ${target_sources_list}
)
