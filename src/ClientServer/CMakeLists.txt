file(GLOB LIB_ClientServer_SRC
     "*.h"
     "*.cpp"
     "*.c"
)

add_library(clientserver STATIC ${LIB_ClientServer_SRC})
target_include_directories(clientserver
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)
target_link_libraries(clientserver
    PUBLIC
        core
        network
        protocol
)
target_compile_options(clientserver
  PRIVATE 
  	$<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
  	$<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
)