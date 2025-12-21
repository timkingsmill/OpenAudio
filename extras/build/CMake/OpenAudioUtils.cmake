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