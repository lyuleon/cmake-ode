cmake_minimum_required(VERSION 3.1)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(externalTest)

set(CMAKE_CXX_STANDARD          11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

find_package(OpenGL REQUIRED)
message(STATUS "Found OpenGL in ${OpenGL_INCLUDE_DIR}")
find_package(X11 REQUIRED)
message(STATUS "Found X11 in ${X11_INCLUDE_DIR}")

#find_package(GLM REQUIRED)
#message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
#find_package(GLFW3 REQUIRED)
#message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

add_definitions(${OPENGL_DEFINITIONS})

add_subdirectory(external/glm)
add_subdirectory(external/nvImage)
add_subdirectory(external/ode)
add_subdirectory(external/glfw)
add_subdirectory(external/vectorial)

add_subdirectory(src/core)
add_subdirectory(src/ClientServer)
add_subdirectory(src/cubes)
add_subdirectory(src/game)
add_subdirectory(src/network)
add_subdirectory(src/protocol)
add_subdirectory(src/virtualgo)


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