file(GLOB LIB_CUBES_SRC
     "*.h"
     "*.cpp"
     "*.c"
)

add_library(cubes STATIC ${LIB_CUBES_SRC})
target_include_directories(cubes
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)
target_link_libraries(cubes
    PUBLIC
		core
		vectorial
)
target_compile_options(cubes
  PRIVATE 
  	$<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
  	$<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
)