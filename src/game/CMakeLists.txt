file(GLOB LIB_GAME_SRC
     "*.h"
     "*.cpp"
     "*.c"
)

set(XLIBS glfw3 pthread GL GLU GLEW X11 Xrandr Xinerama Xi Xxf86vm Xcursor dl)
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
add_definitions(-DCLIENT)
add_executable(Client ${LIB_GAME_SRC})
target_link_libraries(Client ${CLINET_LIB})

remove_definitions(-DCLIENT)
add_executable(Server ${LIB_GAME_SRC})
target_link_libraries(Server ${SERVER_LIB})
