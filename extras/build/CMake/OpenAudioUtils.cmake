include_guard(GLOBAL)
cmake_minimum_required(VERSION 3.22)

include("${JUCE_CMAKE_UTILS_DIR}/JUCEModuleSupport.cmake")


function(openaudio_add_modules)
    openaudio_add_module(
        INSTALL_PATH "include/JUCE-${JUCE_VERSION}/modules"
        ALIAS_NAMESPACE open
        #juce_analytics
        #juce_animation
    )
endfunction()

function(openaudio_add_module target)
    #juce_add_module(
        #${ARGN}
    #)
endfunction()

# -----------------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------------

function(openaudio_add_gui_app target)
    if(CMAKE_SYSTEM_NAME STREQUAL "Android")
        add_library(${target} SHARED)
    else()
        add_executable(${target})
    endif()

    target_compile_definitions(${target} PRIVATE JUCE_STANDALONE_APPLICATION=1)
    _juce_initialise_target(${target} ${ARGN})
    _juce_set_output_name(${target} $<TARGET_PROPERTY:${target},JUCE_PRODUCT_NAME>)
    set_target_properties(${target} PROPERTIES JUCE_TARGET_KIND_STRING "App")
    _juce_configure_bundle(${target} ${target})
    _openaudio_configure_app_bundle(${target} ${target})

    # Dont create a resources target project for the app target
    #_juce_add_resources_rc(${target} ${target})
endfunction()

# -----------------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------------

function(_openaudio_configure_app_bundle source_target dest_target)
    set_target_properties(${dest_target} PROPERTIES
        JUCE_TARGET_KIND_STRING "App"
    #    MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
    )

    #if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    #    set(nib_path "${JUCE_CMAKE_UTILS_DIR}/RecentFilesMenuTemplate.nib")
    #    target_sources("${dest_target}" PRIVATE "${nib_path}")
    #    set_source_files_properties("${nib_path}" PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    #endif()
endfunction()
