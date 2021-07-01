file(GLOB LIBHELLO_SRC
     "*.h"
     "*.cpp"
     "*.c"
)

add_library(nvImage STATIC ${LIBHELLO_SRC})

target_include_directories(nvImage
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib/nvImage)