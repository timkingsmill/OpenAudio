project(openaudio.config VERSION 0.1.0 LANGUAGES C CXX)

add_library(openaudio.config INTERFACE
)

target_sources(openaudio.config
    PRIVATE
        openaudio.config.h
)