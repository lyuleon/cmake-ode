file(GLOB LIB_GAME_SRC
     "*.h"
     "*.cpp"
     "*.c"
)

set(XLIBS glfw3 GL GLU GLEW X11 Xrandr Xinerama Xi Xxf86vm Xcursor dl)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CLINET_LIB	
	glm
	nvImage
	ode
	vectorial
	core
	network
	clientserver
	protocol
	cubes
	virtualgo
	${XLIBS}
)
set(SERVER_LIB	
	glm
	nvImage
	ode
	vectorial
	core
	network
	clientserver
	protocol
	cubes
	virtualgo
)
include_directories(${ODE_INCLUDE_DIR})
add_executable(Client ${LIB_GAME_SRC})
target_compile_definitions(Client PRIVATE CLIENT)
target_link_libraries(Client ${CLINET_LIB})
target_compile_options(Client
  PRIVATE 
  	$<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
  	$<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
  	-DDATA_DIR="${CMAKE_SOURCE_DIR}/data/"
)
add_dependencies(Client libode)

add_executable(Server ${LIB_GAME_SRC})
target_link_libraries(Server ${SERVER_LIB})
target_compile_options(Server
  PRIVATE 
  	$<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
  	$<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
)
add_dependencies(Server libode)
