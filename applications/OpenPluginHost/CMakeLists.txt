set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_FOLDER applications/OpenPluginHost)

project(OpenPluginHost VERSION 0.1.0 LANGUAGES C CXX)

juce_add_gui_app(OpenPluginHost    
    PRODUCT_NAME "OpenPluginHost"
    VERSION ${PROJECT_VERSION}
    BUNDLE_ID "com.openaudio.openpluginhost"
    COMPANY_PRODUCT_NAME "OpenAudio Plugin Host"
    COMPANY_NAME "OpenAudio"
)

# Create the JuceHeader.h for this target.
juce_generate_juce_header(OpenPluginHost)

target_compile_definitions(OpenPluginHost
    PRIVATE
        DONT_SET_USING_JUCE_NAMESPACE=1
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:OpenPluginHost,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:OpenPluginHost,JUCE_VERSION>")


target_include_directories(OpenPluginHost 
    PRIVATE
        include
)

target_sources(OpenPluginHost
    PRIVATE
        Analyser.h
        CustomStandaloneApp.h
        CustomStandaloneApp.cpp
        CustomStandaloneMain.cpp
        CustomStandalone.cpp
        CustomStandaloneFilterWindow.h 
        PluginEditor.cpp
        PluginEditor.h
        PluginProcessor.cpp
        PluginProcessor.h
        ParametricEqualiserEditor.h
        ParametricEqualiserEditor.cpp
        ParametricEqualiserProcessor.h  
        ParametricEqualiserProcessor.cpp
)

#target_link_libraries(OpenPluginHost 
#    PRIVATE 
#        openaudio.eq
#)

target_link_libraries(OpenPluginHost 
    PRIVATE 
        juce::juce_recommended_warning_flags 
        juce::juce_recommended_config_flags 
        juce::juce_recommended_lto_flags
)

target_link_libraries(OpenPluginHost
    PRIVATE 
        juce::juce_gui_extra 
        juce::juce_audio_utils 
        juce::juce_dsp 
        juce::juce_audio_basics 
        juce::juce_audio_plugin_client
        juce::juce_core
)   

# ----------------------------------------------------------------------------------------------




