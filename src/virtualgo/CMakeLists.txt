file(GLOB LIB_VGO_SRC
     "*.h"
     "*.cpp"
     "*.c"
)

add_library(virtualgo STATIC ${LIB_VGO_SRC})
target_include_directories(virtualgo
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(virtualgo
    PUBLIC
        core
        ode
)
