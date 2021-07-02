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

#can ignore lib_output_path, because cmake already configure <include_path> and <lib_path>
#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib/nvImage)