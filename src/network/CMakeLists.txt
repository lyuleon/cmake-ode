file(GLOB LIBNETWORK_SRC
     "*.h"
     "*.cpp"
     "*.c"
)

add_library(network STATIC ${LIBNETWORK_SRC})
target_include_directories(network
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(network
    PUBLIC
        core
)
