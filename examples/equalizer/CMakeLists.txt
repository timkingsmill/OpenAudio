cmake_minimum_required(VERSION 4.2.0)

set(CMAKE_FOLDER examples/equalizer)

project(EQUALIZER_EXAMPLE VERSION 0.0.1)

# If you've installed JUCE somehow (via a package manager, 
# or directly using the CMake install target),
# you'll need to tell this project that it 
# depends on the installed copy of JUCE. 
find_package(JUCE CONFIG REQUIRED)  

juce_add_gui_app(EQUALIZER_EXAMPLE
    PRODUCT_NAME "Equalizer Example"
    VERSION ${PROJECT_VERSION}
    BUNDLE_ID "com.juce.equalizerexample"
    COMPANY_PRODUCT_NAME "OpenAudio Equalizer Example"
    COMPANY_NAME "Tim at OpenAudio"
)

juce_generate_juce_header(EQUALIZER_EXAMPLE)

target_sources(EQUALIZER_EXAMPLE
    PRIVATE
        source/AudioSettingsComponent.cpp
        source/DebugComponent.cpp
        source/Main.cpp
        source/MainComponent.cpp
        source/MainMenuComponent.cpp
        source/MainMenuModel.cpp
        source/EqualizerEditor.cpp
        source/EqualizerProcessor.cpp
        include/AudioSettingsComponent.h
        include/DebugComponent.h
        include/MainMenuComponent.h
        include/MainComponent.h
        include/MainMenuModel.h
        include/EqualizerEditor.h
        include/EqualizerProcessor.h )

target_include_directories(EQUALIZER_EXAMPLE 
    PRIVATE
        include)

target_compile_definitions(EQUALIZER_EXAMPLE
    PRIVATE
        DONT_SET_USING_JUCE_NAMESPACE=1
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:EQUALIZER_EXAMPLE,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:EQUALIZER_EXAMPLE,JUCE_VERSION>")

target_link_libraries(EQUALIZER_EXAMPLE
    PRIVATE
        # GuiAppData            # If we'd created a binary data target, we'd link to it here
        juce::juce_gui_extra
        juce::juce_audio_devices
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

