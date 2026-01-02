project(openaudio.eq VERSION 0.1.0 LANGUAGES C CXX)

add_library(openaudio.eq INTERFACE
)

#add_library(MyProject::MyLibrary ALIAS openaudio.eq)

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