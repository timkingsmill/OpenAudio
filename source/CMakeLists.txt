cmake_minimum_required(VERSION 4.2.0)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# Set C++23 as the default for all targets
set(CMAKE_CXX_STANDARD 23)

add_subdirectory(modules)
add_subdirectory(examples/equalizer)
add_subdirectory(plugins/OpenEQPlugin)

add_subdirectory(applications/OpenDAW)
add_subdirectory(applications/OpenEQ)
add_subdirectory(applications/OpenLookAndFeel)