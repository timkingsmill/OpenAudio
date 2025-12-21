project(patterns VERSION 0.1.0 LANGUAGES C CXX)

add_library(patterns INTERFACE)

target_sources(patterns
    PRIVATE
        source/patterns.cpp
    PUBLIC
    FILE_SET myHeaders
    TYPE HEADERS
    BASE_DIRS
      include
    FILES
      include/patterns.h
)