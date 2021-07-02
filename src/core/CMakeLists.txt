file(GLOB LIB_CORE_SRC
     "*.h"
     "*.cpp"
     "*.c"
)

add_library(core STATIC ${LIB_CORE_SRC})
target_include_directories(core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
