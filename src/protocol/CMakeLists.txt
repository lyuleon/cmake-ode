file(GLOB LIB_PROTOCOL_SRC
     "*.h"
     "*.cpp"
     "*.c"
)

add_library(protocol STATIC ${LIB_PROTOCOL_SRC})
target_include_directories(protocol
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(protocol
    PUBLIC
        core
        network
)
