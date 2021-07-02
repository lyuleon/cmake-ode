set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(EXECUTE_LIB	
	glm
	nvImage
	ode
	glfw
	vectorial
	pthread	
)
add_executable(execute main.cpp)
target_link_libraries(execute ${EXECUTE_LIB})