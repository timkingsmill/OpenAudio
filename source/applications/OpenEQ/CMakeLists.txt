# -----------------------------------------------------------------------------------------------
# OpenEQ executable target.

set(CMAKE_FOLDER OpenAudio/applications/OpenEQ)

project(OpenEQ VERSION 0.1.0 LANGUAGES C CXX)

juce_add_gui_app(OpenEQ
    PRODUCT_NAME "OpenEQ"
    VERSION ${PROJECT_VERSION}
    BUNDLE_ID "com.openaudio.openeq"
    COMPANY_PRODUCT_NAME "OpenAudio EQ"
    COMPANY_NAME "OpenAudio"
)

# Create the JuceHeader.h for this target.
juce_generate_juce_header(OpenEQ)

target_compile_definitions(OpenEQ   
    PRIVATE
        DONT_SET_USING_JUCE_NAMESPACE=1
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:OpenEQ,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:OpenEQ,JUCE_VERSION>")

target_include_directories(OpenEQ    
    PRIVATE 
        include)

# Add the source files for this target.
add_subdirectory(source)

target_link_libraries(OpenEQ
    PRIVATE
        openaudio::openaudio_core
        openaudio::openaudio_eq
)

target_link_libraries(OpenEQ     
    PRIVATE 
        juce::juce_recommended_warning_flags 
        juce::juce_recommended_config_flags 
        juce::juce_recommended_lto_flags
)

target_link_libraries(OpenEQ
    PRIVATE 
        juce::juce_audio_utils 
        juce::juce_audio_devices
        juce::juce_audio_basics 
        juce::juce_audio_plugin_client
        juce::juce_core
        juce::juce_dsp 
        juce::juce_gui_extra 
)

# =================================================================================================
