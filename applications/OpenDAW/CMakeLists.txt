# -----------------------------------------------------------------------------------------------
# OpenDAW executable target.

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_FOLDER applications/OpenDAW)

project(OpenDAW VERSION 0.1.0 LANGUAGES C CXX)

# Set OpenDAW as the startup project in Visual Studio
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT OpenDAW)

openaudio_add_gui_app(OpenDAW
    PRODUCT_NAME "OpenDAW"
    VERSION ${PROJECT_VERSION}
    BUNDLE_ID "com.openaudio.opendaw"
    COMPANY_PRODUCT_NAME "OpenAudio DAW"
    COMPANY_NAME "OpenAudio"
)


# Create the JuceHeader.h for this target.
juce_generate_juce_header(OpenDAW)

target_compile_definitions(OpenDAW
    PRIVATE
        DONT_SET_USING_JUCE_NAMESPACE=1
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:OpenDAW,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:OpenDAW,JUCE_VERSION>")

target_include_directories(OpenDAW 
    PRIVATE
        include)

# Add the include files for this target.
add_subdirectory(include)

# Add the source files for this target.
source_group("My Source Files\\module" 
    FILES
        source/OpenDAW.cpp
)
set(MODULE_SOURCES source/OpenDAW.cpp)
target_sources(OpenDAW
    PRIVATE
        ${MODULE_SOURCES}
)
##add_subdirectory(source)

target_link_libraries(OpenDAW
    PRIVATE 
        openaudio.eq
)

target_link_libraries(OpenDAW 
    PRIVATE 
        juce::juce_recommended_warning_flags 
        juce::juce_recommended_config_flags 
        juce::juce_recommended_lto_flags
)

target_link_libraries(OpenDAW
    PRIVATE 
        juce::juce_gui_extra 
        juce::juce_audio_utils 
        juce::juce_dsp 
        juce::juce_audio_basics 
        juce::juce_core
)   
# -----------------------------------------------------------------------------------------------