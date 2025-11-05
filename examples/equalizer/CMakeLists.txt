cmake_minimum_required(VERSION 3.22)

project(EQUALIZER_EXAMPLE VERSION 0.0.1)

# If you've installed JUCE somehow (via a package manager, 
# or directly using the CMake install target),
# you'll need to tell this project that it 
# depends on the installed copy of JUCE. 
find_package(JUCE CONFIG REQUIRED)  

juce_add_gui_app(EQUALIZER_EXAMPLE
    PRODUCT_NAME "Equalizer Example"
    VERSION ${PROJECT_VERSION}
    COMPANY_NAME "Your Company"
)

target_sources(EQUALIZER_EXAMPLE
    PRIVATE
        Main.cpp
        MainComponent.cpp)

target_compile_definitions(EQUALIZER_EXAMPLE
    PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:EQUALIZER_EXAMPLE,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:EQUALIZER_EXAMPLE,JUCE_VERSION>")

target_link_libraries(EQUALIZER_EXAMPLE
    PRIVATE
        # GuiAppData            # If we'd created a binary data target, we'd link to it here
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

